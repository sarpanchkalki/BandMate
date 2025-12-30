#include "DroneInstrument.h"
#include "AudioConfig.h"
#include <cmath>
#include <iostream>

DroneInstrument::DroneInstrument()
    : frequency_(0.0f),
      velocity_(0.0f),
      active_(false),
      phase_(0.0f),
      lfoPhase_(0.0f) {}

void DroneInstrument::prepare(const Session&) {
    std::cout << "Drone prepared for session" << std::endl;
}

void DroneInstrument::noteOn(float frequency,
                             NoteDuration,
                             float velocity) {
    frequency_ = frequency;
    velocity_ = velocity;
    active_ = true;

    std::cout << "Drone ON | freq: "
              << frequency_
              << " | vel: "
              << velocity_
              << std::endl;
}

void DroneInstrument::process(float* output, int frames) {
    if (!active_) return;

    float phaseInc = 2.0f * static_cast<float>(M_PI) * frequency_ / SAMPLE_RATE;
    float lfoInc   = 2.0f * static_cast<float>(M_PI) * 0.1f / SAMPLE_RATE; // slow breathing

    for (int i = 0; i < frames; ++i) {
        // harmonic content
        float fundamental = std::sin(phase_);
        float h2 = std::sin(phase_ * 2.0f) * 0.3f;
        float h3 = std::sin(phase_ * 3.0f) * 0.15f;

        // slow amplitude modulation (breathing)
        float lfo = 0.85f + 0.15f * std::sin(lfoPhase_);

float accent = 1.0f;


        float sample = (fundamental + h2 + h3) * lfo * velocity_;

        output[i] += sample;

        phase_ += phaseInc;
        if (phase_ >= 2.0f * static_cast<float>(M_PI))
            phase_ -= 2.0f * static_cast<float>(M_PI);

        lfoPhase_ += lfoInc;
        if (lfoPhase_ >= 2.0f * static_cast<float>(M_PI))
            lfoPhase_ -= 2.0f * static_cast<float>(M_PI);
    }
}

void DroneInstrument::stop() {
    active_ = false;
    std::cout << "Drone OFF" << std::endl;
}
