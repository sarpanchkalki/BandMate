#include "PitchDetector.h"
#include "AudioConfig.h"
#include <cmath>

PitchDetector::PitchDetector()
    : lastFrequency_(0.0f) {}

void PitchDetector::process(const float* input, int frames) {
    // Autocorrelation (very simplified, low CPU)
    int minLag = SAMPLE_RATE / 1000; // 1000 Hz
    int maxLag = SAMPLE_RATE / 60;   // 60 Hz

    float bestCorr = 0.0f;
    int bestLag = 0;

    for (int lag = minLag; lag <= maxLag; ++lag) {
        float corr = 0.0f;
        for (int i = 0; i < frames - lag; ++i) {
            corr += input[i] * input[i + lag];
        }
        if (corr > bestCorr) {
            bestCorr = corr;
            bestLag = lag;
        }
    }

    if (bestLag > 0) {
        lastFrequency_ = static_cast<float>(SAMPLE_RATE) / bestLag;
    }
}

float PitchDetector::detectedFrequency() const {
    return lastFrequency_;
}
