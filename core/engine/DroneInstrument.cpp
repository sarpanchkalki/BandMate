#include "DroneInstrument.h"
#include "AudioConfig.h"
#include <cmath>
#include <iostream>

DroneInstrument::DroneInstrument()
    : frequency_(0.0f),
      velocity_(0.0f),
      active_(false),
      phase_(0.0f) {}

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

    float phaseIncrement =
        2.0f * static_cast<float>(M_PI) * frequency_ / SAMPLE_RATE;

    for (int i = 0; i < frames; ++i) {
        float sample = std::sin(phase_) * velocity_;
        output[i] += sample;

        phase_ += phaseIncrement;
        if (phase_ >= 2.0f * static_cast<float>(M_PI))
            phase_ -= 2.0f * static_cast<float>(M_PI);
    }
}

void DroneInstrument::stop() {
    active_ = false;
    std::cout << "Drone OFF" << std::endl;
}
