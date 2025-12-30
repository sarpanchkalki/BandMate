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
    bool downbeat = clock_.isDownbeat();

    // trigger metronome on beat
if (clock_.isOnBeat(1.0)) {
 metronome_.trigger(downbeat);
    rhythm_.triggerBeat(downbeat);
    }

    // process instruments
    for (auto& i : instruments_) {
        i->process(output, frames);
rhythm_.process(output, frames);
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
