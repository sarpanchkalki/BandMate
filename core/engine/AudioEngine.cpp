#include "AudioEngine.h"
#include <iostream>

AudioEngine::AudioEngine()
    : dynamics_(0.5f) {}

void AudioEngine::setSession(const Session& session) {
    session_ = session;
    timeEngine_.setTempo(session_.tempo);
    dynamics_.setEnergy(session_.energy);

    rhythm_.setCycleLength(4);
    rhythm_.setPattern({0, 2});
}

void AudioEngine::addInstrument(std::unique_ptr<Instrument> instrument) {
    instruments_.push_back(std::move(instrument));
}

void AudioEngine::prepare() {
    std::cout << "AudioEngine prepared" << std::endl;
    for (auto& inst : instruments_) {
        inst->prepare(session_);
    }
}

void AudioEngine::process(float* output, int frames) {
    float deltaSeconds = frames / 48000.0f;
    timeEngine_.update(deltaSeconds);

    for (auto& inst : instruments_) {
        inst->process(output, frames);
    }
}

void AudioEngine::start() {
    std::cout << "Engine started" << std::endl;

    // Start drone on Sa
    if (!instruments_.empty()) {
        instruments_[0]->noteOn(
            session_.key.rootFrequency,
            NoteDuration::WHOLE,
            dynamics_.velocity()
        );
    }
}

void AudioEngine::stop() {
    for (auto& inst : instruments_) {
        inst->stop();
    }

    std::cout << "AudioEngine stopped" << std::endl;
}
