#include "WASAPIOutput.h"

#include <windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <algorithm>

#ifndef KSDATAFORMAT_SUBTYPE_IEEE_FLOAT
#include <initguid.h>
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_IEEE_FLOAT,
0x00000003, 0x0000, 0x0010,
0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
#endif


WASAPIOutput::WASAPIOutput() = default;

WASAPIOutput::~WASAPIOutput() {
    if (mixFormat_) {
        CoTaskMemFree(mixFormat_);
        mixFormat_ = nullptr;
    }
}


static const float kFloatMax = 1.0f;
static const float kFloatMin = -1.0f;

void WASAPIOutput::start(const std::function<void(float*, int)>& renderCallback) {
    HRESULT hr;

    hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::cerr << "CoInitialize failed\n";
        return;
    }

    IMMDeviceEnumerator* deviceEnumerator = nullptr;
    IMMDevice* device = nullptr;

    hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator),
        nullptr,
        CLSCTX_ALL,
        __uuidof(IMMDeviceEnumerator),
        (void**)&deviceEnumerator
    );
    if (FAILED(hr)) return;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device);
    if (FAILED(hr)) return;

    hr = device->Activate(
        __uuidof(IAudioClient),
        CLSCTX_ALL,
        nullptr,
        (void**)&audioClient_
    );
    if (FAILED(hr)) return;

    hr = audioClient_->GetMixFormat(&mixFormat_);
    if (FAILED(hr)) return;

    hr = audioClient_->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        0,
        10000000,   // 1 second buffer
        0,
        mixFormat_,
        nullptr
    );
    if (FAILED(hr)) {
        std::cerr << "AudioClient Initialize failed\n";
        return;
    }

    hr = audioClient_->GetService(__uuidof(IAudioRenderClient),
                                  (void**)&renderClient_);
    if (FAILED(hr)) return;

    UINT32 bufferFrameCount;
    audioClient_->GetBufferSize(&bufferFrameCount);

    std::vector<float> engineBuffer(bufferFrameCount);

    // Detect format
bool isFloat = false;

if (mixFormat_->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
    isFloat = true;
}
else if (mixFormat_->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
         mixFormat_->wBitsPerSample == 32) {
    isFloat = true;
}


    audioClient_->Start();

    while (true) {
        UINT32 padding = 0;
        audioClient_->GetCurrentPadding(&padding);

        UINT32 framesAvailable = bufferFrameCount - padding;
        if (framesAvailable == 0) {
            Sleep(1);
            continue;
        }

        BYTE* data = nullptr;
        hr = renderClient_->GetBuffer(framesAvailable, &data);
        if (FAILED(hr)) break;

        // Render mono float audio from engine
        renderCallback(engineBuffer.data(), framesAvailable);

        if (isFloat) {
            float* out = reinterpret_cast<float*>(data);
            for (UINT32 i = 0; i < framesAvailable; ++i) {
                float s = std::clamp(engineBuffer[i], kFloatMin, kFloatMax);
                out[i * 2]     = s;
                out[i * 2 + 1] = s;
            }
        } else {
            int16_t* out = reinterpret_cast<int16_t*>(data);
            for (UINT32 i = 0; i < framesAvailable; ++i) {
                float s = std::clamp(engineBuffer[i], kFloatMin, kFloatMax);
                int16_t v = static_cast<int16_t>(s * 32767.0f);
                out[i * 2]     = v;
                out[i * 2 + 1] = v;
            }
        }

        renderClient_->ReleaseBuffer(framesAvailable, 0);
    }

    audioClient_->Stop();
}

void WASAPIOutput::stop() {
    if (audioClient_) {
        audioClient_->Stop();
    }
}
