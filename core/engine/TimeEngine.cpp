#include "TimeEngine.h"

TimeEngine::TimeEngine()
    : secondsPerBeat_(0.5f),
      accumulator_(0.0f),
      beatCount_(0) {}

void TimeEngine::setTempo(float bpm) {
    secondsPerBeat_ = 60.0f / bpm;
}

void TimeEngine::update(float deltaSeconds) {
    accumulator_ += deltaSeconds;

    while (accumulator_ >= secondsPerBeat_) {
        accumulator_ -= secondsPerBeat_;
        beatCount_++;
    }
}

int TimeEngine::getBeatCount() const {
    return beatCount_;
}

float TimeEngine::beatsToSeconds(float beats) const {
    return beats * secondsPerBeat_;
}
