#include "AudioEngine.h"
#include "AudioConfig.h"
#include "WavWriter.h"
#include <iostream>
#include <vector>

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
    std::cout << "AudioEngine prepared" << std::endl;
    for (auto& inst : instruments_) {
        inst->prepare(session_);
    }
}

void AudioEngine::process(float*, int) {}

void AudioEngine::start() {
    std::cout << "Engine started" << std::endl;

    const int seconds = 3;
    const int frames = SAMPLE_RATE * seconds;

    std::vector<float> buffer(frames, 0.0f);

    instruments_[0]->noteOn(
        session_.key.rootFrequency,
        NoteDuration::WHOLE,
        dynamics_.velocity()
    );

    instruments_[0]->process(buffer.data(), frames);

    WavWriter::writeMono16("tanpura.wav", buffer, SAMPLE_RATE);

    std::cout << "WAV written: tanpura.wav" << std::endl;
}

void AudioEngine::stop() {
    for (auto& inst : instruments_) {
        inst->stop();
    }
    std::cout << "AudioEngine stopped" << std::endl;
}
