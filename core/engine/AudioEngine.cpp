#include "AudioEngine.h"
#include "AudioConfig.h"
#include <iostream>
#include <vector>

AudioEngine::AudioEngine()
    : dynamics_(0.5f) {}

void AudioEngine::setSession(const Session& session) {
    session_ = session;
    timeEngine_.setTempo(session_.tempo);
    dynamics_.setEnergy(session_.energy);
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

void AudioEngine::process(float*, int) {}

void AudioEngine::start() {
    std::cout << "Engine started" << std::endl;

    const int frames = 256;
    std::vector<float> buffer(frames, 0.0f);

    // Start drone
    instruments_[0]->noteOn(
        session_.key.rootFrequency,
        NoteDuration::WHOLE,
        dynamics_.velocity()
    );

    // Generate audio
    instruments_[0]->process(buffer.data(), frames);

    // Print first few samples
    std::cout << "First 10 audio samples:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << buffer[i] << std::endl;
    }
}

void AudioEngine::stop() {
    for (auto& inst : instruments_) {
        inst->stop();
    }

    std::cout << "AudioEngine stopped" << std::endl;
}

