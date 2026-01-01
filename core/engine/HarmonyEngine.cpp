#include "HarmonyEngine.h"

HarmonyEngine::HarmonyEngine() {
    rootFreq_ = 261.63f;
    chordIndex_ = 0;
}

void HarmonyEngine::setRootFrequency(float freq) {
    rootFreq_ = freq;
}

void HarmonyEngine::setChordDegree(int degree) {
    chordIndex_ = degree;
}

void HarmonyEngine::process(float* output, int frames) {
    // MVP: harmony is implied, not rendered yet
    (void)output;
    (void)frames;
}
