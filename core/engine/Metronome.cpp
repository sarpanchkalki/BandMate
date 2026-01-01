#include "Metronome.h"

Metronome::Metronome() {
    remainingSamples_ = 0;
    accentLevel_ = 0.15f;
}

void Metronome::trigger(bool) {
    remainingSamples_ = 100;
}

void Metronome::process(float* output, int frames) {
    for (int i = 0; i < frames && remainingSamples_ > 0; ++i) {
        output[i] += accentLevel_;
        remainingSamples_--;
    }
}
