#include "RhythmEngine.h"

RhythmEngine::RhythmEngine()
    : cycleLength_(4) {}

void RhythmEngine::setCycleLength(int beats) {
    cycleLength_ = beats;
}

void RhythmEngine::setPattern(const std::vector<int>& pattern) {
    activeBeats_ = pattern;
}

bool RhythmEngine::isBeatActive(int beat) const {
    int position = beat % cycleLength_;
    for (int b : activeBeats_) {
        if (b == position) return true;
    }
    return false;
}
