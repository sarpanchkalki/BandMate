#include "WASAPIInput.h"
#include <windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <thread>

bool WASAPIInput::start(const std::function<void(const float*, int)>& callback) {
    std::thread([callback]() {
        CoInitialize(nullptr);

        IMMDeviceEnumerator* enumerator = nullptr;
        IMMDevice* device = nullptr;
        IAudioClient* client = nullptr;
        IAudioCaptureClient* capture = nullptr;

        CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
            CLSCTX_ALL, IID_PPV_ARGS(&enumerator));

        enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &device);
        device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&client);

        WAVEFORMATEX* format = nullptr;
        client->GetMixFormat(&format);

        client->Initialize(AUDCLNT_SHAREMODE_SHARED,
            0, 10000000, 0, format, nullptr);

        client->GetService(IID_PPV_ARGS(&capture));
        client->Start();

        while (true) {
            UINT32 frames;
            BYTE* data;
            DWORD flags;

            capture->GetNextPacketSize(&frames);
            if (frames > 0) {
                capture->GetBuffer(&data, &frames, &flags, nullptr, nullptr);
                callback((float*)data, frames);
                capture->ReleaseBuffer(frames);
            }
            Sleep(5);
        }
    }).detach();

    return true;
}
