#include "LeadEngine.h"

LeadEngine::LeadEngine()
    : chordDegree_(1),
      lastBar_(-1),
      energy_(0.5f) {}

void LeadEngine::reset() {
    chordDegree_ = 1;
    lastBar_ = -1;
    energy_ = 0.5f;
}

void LeadEngine::advance(double currentBar) {
    int bar = static_cast<int>(currentBar);

    if (bar != lastBar_) {
        nextChord();

        energy_ += 0.05f;
        if (energy_ > 0.85f)
            energy_ = 0.5f;

        lastBar_ = bar;
    }
}

void LeadEngine::nextChord() {
    if (chordDegree_ == 1)
        chordDegree_ = 4;
    else if (chordDegree_ == 4)
        chordDegree_ = 5;
    else
        chordDegree_ = 1;
}

int LeadEngine::currentChordDegree() const {
    return chordDegree_;
}

float LeadEngine::currentEnergy() const {
    return energy_;
}
