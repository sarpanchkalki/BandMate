#include "HarmonyEngine.h"
#include "AudioConfig.h"
#include <cmath>

HarmonyEngine::HarmonyEngine()
    : rootFreq_(261.63f),
      chordIndex_(0) {
    phase_[0] = phase_[1] = phase_[2] = 0.0f;
}

void HarmonyEngine::setRootFrequency(float root) {
    rootFreq_ = root;
}

void HarmonyEngine::triggerBar() {
    chordIndex_ = (chordIndex_ + 1) % 4;
}

void HarmonyEngine::process(float* output, int frames) {
    // I – IV – V – I
    static const float ratios[4][3] = {
        {1.0f, 1.25f, 1.5f},   // I
        {1.25f, 1.5f, 1.875f}, // IV
        {1.5f, 1.875f, 2.25f}, // V
        {1.0f, 1.25f, 1.5f}    // I
    };

    const float* chord = ratios[chordIndex_];

    for (int i = 0; i < frames; ++i) {
        float sample = 0.0f;

        for (int v = 0; v < 3; ++v) {
            float freq = rootFreq_ * chord[v];
            float inc = 2.0f * static_cast<float>(M_PI) * freq / SAMPLE_RATE;
            sample += std::sin(phase_[v]) * 0.08f;
            phase_[v] += inc;
            if (phase_[v] >= 2.0f * static_cast<float>(M_PI))
                phase_[v] -= 2.0f * static_cast<float>(M_PI);
        }

        output[i] += sample;
    }
}
