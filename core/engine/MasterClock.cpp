#include "MasterClock.h"
#include <cmath>

MasterClock::MasterClock()
    : sampleRate_(48000),
      bpm_(120.0f),
      numerator_(4),
      denominator_(4),
      sampleCounter_(0) {
    samplesPerBeat_ = (60.0 / bpm_) * sampleRate_;
}

void MasterClock::setSampleRate(int sr) {
    sampleRate_ = sr;
    samplesPerBeat_ = (60.0 / bpm_) * sampleRate_;
}

void MasterClock::setTempo(float bpm) {
    bpm_ = bpm;
    samplesPerBeat_ = (60.0 / bpm_) * sampleRate_;
}

void MasterClock::setTimeSignature(int num, int den) {
    numerator_ = num;
    denominator_ = den;
}

void MasterClock::advance(int frames) {
    sampleCounter_ += frames;
}

double MasterClock::currentBeat() const {
    return sampleCounter_ / samplesPerBeat_;
}

double MasterClock::currentBar() const {
    return currentBeat() / numerator_;
}

bool MasterClock::isOnBeat(double subdivision) const {
    double beat = currentBeat() * subdivision;
    return std::fabs(beat - std::round(beat)) < 0.0001;
}
bool MasterClock::isDownbeat() const {
    double beat = currentBeat();
    int beatIndex = static_cast<int>(std::floor(beat)) % numerator_;
    return beatIndex == 0;
}
