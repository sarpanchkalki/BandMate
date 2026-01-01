#include "FollowEngine.h"
#include <cmath>

FollowEngine::FollowEngine()
    : rootFreq_(261.63f),
      lastDegree_(0) {}

void FollowEngine::setScaleRoot(float root) {
    rootFreq_ = root;
}

void FollowEngine::updateInputPitch(float freq) {
    if (freq <= 0.0f) return;

    float ratio = freq / rootFreq_;

    // Rough diatonic degree detection
    if (ratio < 1.15f)      lastDegree_ = 0; // I
    else if (ratio < 1.35f) lastDegree_ = 1; // II
    else if (ratio < 1.55f) lastDegree_ = 2; // III
    else if (ratio < 1.75f) lastDegree_ = 3; // IV
    else                    lastDegree_ = 4; // V
}

int FollowEngine::suggestedChordDegree() const {
    return lastDegree_;
}
