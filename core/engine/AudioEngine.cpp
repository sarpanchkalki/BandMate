#include "AudioEngine.h"
#include <cstring>

AudioEngine::AudioEngine()
    : dynamics_(0.5f) {}

void AudioEngine::setSession(const Session& session) {
    session_ = session;
    dynamics_.setEnergy(session_.energy);
}

void AudioEngine::addInstrument(std::unique_ptr<Instrument> instrument) {
    instruments_.push_back(std::move(instrument));
}

void AudioEngine::prepare() {
    for (auto& i : instruments_)
        i->prepare(session_);

    instruments_[0]->noteOn(
        session_.key.rootFrequency,
        NoteDuration::WHOLE,
        dynamics_.velocity()
    );
}
#include <iostream>
#include <cstring>

void AudioEngine::render(float* output, int frames) {
    std::memset(output, 0, frames * sizeof(float));

    for (auto& i : instruments_) {
        i->process(output, frames);
    }

    // DEBUG: print first 5 samples ONCE
    static bool printed = false;
    if (!printed) {
        printed = true;
        std::cout << "DEBUG samples:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << output[i] << std::endl;
        }
    }
}

