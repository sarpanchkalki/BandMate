#include "Metronome.h"

Metronome::Metronome()
    : remainingSamples_(0), accentLevel_(0.15f) {}

void Metronome::trigger(bool strong) {
    remainingSamples_ = 120;
    accentLevel_ = strong ? 0.30f : 0.12f;
}

void Metronome::process(float* output, int frames) {
    static unsigned int seed = 1;

    for (int i = 0; i < frames && remainingSamples_ > 0; ++i) {
        seed = seed * 1664525u + 1013904223u;
        float noise = ((seed >> 16) & 0x7FFF) / 16384.0f - 1.0f;

        float env = remainingSamples_ / 120.0f;
        output[i] += noise * env * accentLevel_;
        remainingSamples_--;
    }
}
