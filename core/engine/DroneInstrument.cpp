#include "DroneInstrument.h"
#include <iostream>

DroneInstrument::DroneInstrument()
    : frequency_(0.0f),
      velocity_(0.0f),
      active_(false) {}

void DroneInstrument::prepare(const Session& session) {
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

void DroneInstrument::process(float*, int) {
    if (!active_) return;
    // audio generation will come later
}

void DroneInstrument::stop() {
    active_ = false;
    std::cout << "Drone OFF" << std::endl;
}
