#include "RhythmEngine.h"

RhythmEngine::RhythmEngine()
    : remainingSamples_(0),
      accentLevel_(0.12f) {}

void RhythmEngine::setTempo(float) {
    // reserved for groove later
}

void RhythmEngine::triggerBeat(bool downbeat) {
    remainingSamples_ = downbeat ? 220 : 140;
    accentLevel_ = downbeat ? 0.35f : 0.18f;
}

void RhythmEngine::process(float* output, int frames) {
    static unsigned int seed = 7;

    for (int i = 0; i < frames && remainingSamples_ > 0; ++i) {
        seed = seed * 1664525u + 1013904223u;
        float noise = ((seed >> 16) & 0x7FFF) / 16384.0f - 1.0f;

        float env = remainingSamples_ / 220.0f;
        output[i] += noise * env * accentLevel_;
        remainingSamples_--;
    }
}
