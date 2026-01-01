#include "RhythmEngine.h"

RhythmEngine::RhythmEngine() {
    remainingSamples_ = 0;
}

void RhythmEngine::triggerBeat(bool) {
    remainingSamples_ = 120;
}

void RhythmEngine::process(float* output, int frames) {
    for (int i = 0; i < frames && remainingSamples_ > 0; ++i) {
        output[i] += 0.05f;
        remainingSamples_--;
    }
}

