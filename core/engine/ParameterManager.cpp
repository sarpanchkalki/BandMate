#include "ParameterManager.h"

ParameterManager::ParameterManager() {
    params_.tempoBPM = 60.0f;
    params_.energy = 0.5f;
    params_.rootFrequency = 261.63f; // Sa / C
    params_.scaleType = 0;
    params_.mode = PlayMode::NEUTRAL;
}

void ParameterManager::setParameters(const MusicalParameters& params) {
    params_ = params;
}

const MusicalParameters& ParameterManager::current() const {
    return params_;
}
