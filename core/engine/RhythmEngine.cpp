#include "RhythmEngine.h"
#include <cstdlib>

RhythmEngine::RhythmEngine()
    : remainingSamples_(0),
      accentLevel_(0.12f) {}

void RhythmEngine::setTempo(float) {
    // reserved for swing / groove later
}

void RhythmEngine::triggerBeat(bool downbeat) {
    remainingSamples_ = downbeat ? 220 : 140;   // longer on sam
    accentLevel_ = downbeat ? 0.35f : 0.18f;
}

void RhythmEngine::process(float* output, int frames) {
    for (int i = 0; i < frames && remainingSamples_ > 0; ++i) {
        float noise = ((std::rand() / (float)RAND_MAX) * 2.0f - 1.0f);
        float env = remainingSamples_ / 220.0f;
        output[i] += noise * env * accentLevel_;
        remainingSamples_--;
    }
}
