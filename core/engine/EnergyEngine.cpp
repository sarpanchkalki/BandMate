#include "EnergyEngine.h"
#include "AudioConfig.h"
#include <cmath>

EnergyEngine::EnergyEngine()
    : baseEnergy_(0.5f),
      phase_(0.0f),
      currentEnergy_(0.5f) {}

void EnergyEngine::setBaseEnergy(float energy) {
    baseEnergy_ = energy;
}

void EnergyEngine::advance(int frames) {
    // very slow musical modulation (~16 bars)
    float lfoFreq = 0.01f;
    float inc = 2.0f * static_cast<float>(M_PI) * lfoFreq / SAMPLE_RATE;

    for (int i = 0; i < frames; ++i) {
        phase_ += inc;
        if (phase_ > 2.0f * static_cast<float>(M_PI))
            phase_ -= 2.0f * static_cast<float>(M_PI);
    }

    float mod = 0.15f * std::sin(phase_);
    currentEnergy_ = baseEnergy_ + mod;

    if (currentEnergy_ < 0.0f) currentEnergy_ = 0.0f;
    if (currentEnergy_ > 1.0f) currentEnergy_ = 1.0f;
}

float EnergyEngine::value() const {
    return currentEnergy_;
}
