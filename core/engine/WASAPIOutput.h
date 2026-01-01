#ifndef WASAPI_OUTPUT_H
#define WASAPI_OUTPUT_H

#include <windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <functional>

class WASAPIOutput {
public:
    WASAPIOutput();
    ~WASAPIOutput();

    bool init(int sampleRate, int bufferFrames);
    void start(const std::function<void(float*, int)>& renderCallback);
    void stop();

private:
    IMMDevice* device_;
    IAudioClient* audioClient_;
    IAudioRenderClient* renderClient_;
    HANDLE event_;
    int bufferFrames_;
WAVEFORMATEX* mixFormat_ = nullptr;

};

#endif
