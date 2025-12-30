#include "AudioEngine.h"
#include "NoteDuration.h"
#include <iostream>
#include <cmath>

AudioEngine::AudioEngine() {}

void AudioEngine::setSession(const Session& session) {
    session_ = session;
    timeEngine_.setTempo(session_.tempo);
}

void AudioEngine::prepare() {
    std::cout << "AudioEngine prepared" << std::endl;
}

void AudioEngine::process(float* output, int frames) {
    float deltaSeconds = frames / 48000.0f;
    timeEngine_.update(deltaSeconds);
}

void AudioEngine::start() {
    std::cout << "Engine started | Tempo: "
              << session_.tempo
              << " | Energy: "
              << session_.energy
              << std::endl;

    // Test duration logic
    float quarter = durationToBeats(NoteDuration::QUARTER);
    float seconds = timeEngine_.beatsToSeconds(quarter);

    std::cout << "Quarter note duration (seconds): "
              << seconds
              << std::endl;
}

void AudioEngine::stop() {
    std::cout << "Total beats counted: "
              << timeEngine_.getBeatCount()
              << std::endl;

    std::cout << "AudioEngine stopped" << std::endl;
}
