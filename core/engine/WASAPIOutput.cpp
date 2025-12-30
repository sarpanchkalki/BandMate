#include "WASAPIOutput.h"

#include <windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

#define SAFE_RELEASE(x) if(x){ x->Release(); x = nullptr; }

WASAPIOutput::WASAPIOutput()
    : device_(nullptr),
      audioClient_(nullptr),
      renderClient_(nullptr),
      bufferFrames_(0) {}

WASAPIOutput::~WASAPIOutput() {
    stop();
    SAFE_RELEASE(renderClient_);
    SAFE_RELEASE(audioClient_);
    SAFE_RELEASE(device_);
    CoUninitialize();
}

bool WASAPIOutput::init(int, int) {
    HRESULT hr;
    CoInitialize(nullptr);

    IMMDeviceEnumerator* enumerator = nullptr;

    hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator),
        nullptr,
        CLSCTX_ALL,
        __uuidof(IMMDeviceEnumerator),
        (void**)&enumerator
    );
    if (FAILED(hr)) {
        std::cout << "Failed to create device enumerator" << std::endl;
        return false;
    }

    hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device_);
    enumerator->Release();
    if (FAILED(hr)) {
        std::cout << "Failed to get default audio endpoint" << std::endl;
        return false;
    }

    hr = device_->Activate(
        __uuidof(IAudioClient),
        CLSCTX_ALL,
        nullptr,
        (void**)&audioClient_
    );
    if (FAILED(hr)) {
        std::cout << "Failed to activate audio client" << std::endl;
        return false;
    }

    // 🔴 THIS IS THE IMPORTANT PART — GET MIX FORMAT
    WAVEFORMATEX* mixFormat = nullptr;
    hr = audioClient_->GetMixFormat(&mixFormat);
    if (FAILED(hr)) {
        std::cout << "GetMixFormat failed" << std::endl;
        return false;
    }

    // 🔎 PRINT MIX FORMAT (THIS IS WHAT WE NEED)
std::cout << "==============================" << std::endl;
std::cout << "WASAPI MIX FORMAT" << std::endl;
std::cout << "Channels: " << mixFormat->nChannels << std::endl;
std::cout << "Sample rate: " << mixFormat->nSamplesPerSec << std::endl;
std::cout << "Bits per sample: " << mixFormat->wBitsPerSample << std::endl;
std::cout << "Format tag: " << mixFormat->wFormatTag << std::endl;

if (mixFormat->wFormatTag == 1)
    std::cout << "Format: PCM" << std::endl;
else if (mixFormat->wFormatTag == 3)
    std::cout << "Format: FLOAT" << std::endl;
else if (mixFormat->wFormatTag == 65534)
    std::cout << "Format: EXTENSIBLE" << std::endl;
else
    std::cout << "Format: OTHER" << std::endl;

std::cout << "==============================" << std::endl;

    // ✅ Initialize WASAPI using THE MIX FORMAT
    hr = audioClient_->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        0,
        10000000,   // 1 second buffer
        0,
        mixFormat,
        nullptr
    );

    CoTaskMemFree(mixFormat);

    if (FAILED(hr)) {
        std::cout << "AudioClient Initialize failed" << std::endl;
        return false;
    }

    hr = audioClient_->GetService(
        __uuidof(IAudioRenderClient),
        (void**)&renderClient_
    );
    if (FAILED(hr)) {
        std::cout << "Failed to get render client" << std::endl;
        return false;
    }

    hr = audioClient_->GetBufferSize((UINT32*)&bufferFrames_);
    if (FAILED(hr)) {
        std::cout << "Failed to get buffer size" << std::endl;
        return false;
    }

    return true;
}

void WASAPIOutput::start(const std::function<void(float*, int)>& renderCallback) {
    HRESULT hr;
    audioClient_->Start();

    const int channels = 2;
    std::vector<float> engineBuffer(bufferFrames_);

    while (true) {
        UINT32 padding = 0;
        hr = audioClient_->GetCurrentPadding(&padding);
        if (FAILED(hr)) break;

        UINT32 framesAvailable = bufferFrames_ - padding;
        if (framesAvailable == 0) {
            Sleep(1);
            continue;
        }

        BYTE* data = nullptr;
        hr = renderClient_->GetBuffer(framesAvailable, &data);
        if (FAILED(hr)) break;

        // Generate mono audio
        renderCallback(engineBuffer.data(), framesAvailable);

        // Interleave mono → stereo float
        float* out = reinterpret_cast<float*>(data);
        for (UINT32 i = 0; i < framesAvailable; ++i) {
            float s = engineBuffer[i];
            out[i * 2]     = s; // Left
            out[i * 2 + 1] = s; // Right
        }

        renderClient_->ReleaseBuffer(framesAvailable, 0);
    }

    audioClient_->Stop();
}


void WASAPIOutput::stop() {
    if (audioClient_) audioClient_->Stop();
}
