#include "Dynamics.h"
#include <algorithm>

Dynamics::Dynamics(float energy)
    : energy_(std::clamp(energy, 0.0f, 1.0f)) {}

void Dynamics::setEnergy(float energy) {
    energy_ = std::clamp(energy, 0.0f, 1.0f);
}

float Dynamics::velocity() const {
    // Simple expressive curve
    return 0.2f + (energy_ * 0.8f);
}
