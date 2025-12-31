#include "AudioEngine.h"
#include <cstring>
#include <iostream>

AudioEngine::AudioEngine()
    : dynamics_(0.5f) {}

void AudioEngine::setSession(const Session& session) {
    session_ = session;
    dynamics_.setEnergy(session_.energy);

    clock_.setSampleRate(48000);
    clock_.setTempo(session_.tempo);
    clock_.setTimeSignature(4, 4);
harmony_.setRootFrequency(session_.key.rootFrequency);
energy_.setBaseEnergy(session_.energy);


}

void AudioEngine::addInstrument(std::unique_ptr<Instrument> instrument) {
    instruments_.push_back(std::move(instrument));
}

void AudioEngine::prepare() {
    for (auto& i : instruments_) {
        i->prepare(session_);
    }

    instruments_[0]->noteOn(
        session_.key.rootFrequency,
        NoteDuration::WHOLE,
        dynamics_.velocity()
    );
}

void AudioEngine::render(float* output, int frames) {
    std::memset(output, 0, frames * sizeof(float));

    // advance master clock
    clock_.advance(frames);
energy_.advance(frames);
float energy = energy_.value();

bool downbeat = clock_.isDownbeat();
static int lastBar = -1;
int currentBar = static_cast<int>(clock_.currentBar());

if (currentBar != lastBar) {
    harmony_.triggerBar();
    lastBar = currentBar;

// master gain + hard safety clamp
for (int i = 0; i < frames; ++i) {
    output[i] *= 0.6f;   // headroom
    if (output[i] > 1.0f) output[i] = 1.0f;
    if (output[i] < -1.0f) output[i] = -1.0f;
}

float masterGain = 0.4f + 0.4f * energy;

for (int i = 0; i < frames; ++i) {
    output[i] *= masterGain;
    if (output[i] > 1.0f) output[i] = 1.0f;
    if (output[i] < -1.0f) output[i] = -1.0f;
}


}

    // trigger metronome on beat
if (clock_.isOnBeat(1.0)) {
 metronome_.trigger(downbeat);
    rhythm_.triggerBeat(downbeat);
    }

bool lastBeatState_ = false;

bool onBeat = clock_.isOnBeat(1.0);
if (onBeat && !lastBeatState_) {
    metronome_.trigger(downbeat);
    rhythm_.triggerBeat(downbeat);
}
lastBeatState_ = onBeat;

    // process instruments
    for (auto& i : instruments_) {
        i->process(output, frames);
rhythm_.process(output, frames);
harmony_.process(output, frames);


    }

 // subtle accent on downbeat (post-instrument)
    if (downbeat) {
        for (int i = 0; i < frames; ++i) {
            output[i] *= 1.05f; // VERY subtle
        }
    }

    // add metronome click
    metronome_.process(output, frames);
}
