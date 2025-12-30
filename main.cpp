#include <iostream>
#include "core/engine/AudioEngine.h"

int main() {
    Session session;
    session.mode = Mode::FOLLOW;
    session.tempo = 60.0f;   // 1 beat per second
    session.energy = 0.7f;

    session.key.rootFrequency = 261.63f;
    session.key.scale = ScaleType::MAJOR;

    AudioEngine engine;
    engine.setSession(session);

    engine.prepare();
    engine.start();

    // Simulate running for ~5 seconds
    for (int i = 0; i < 5; ++i) {
        engine.process(nullptr, 48000); // 1 second
    }

    engine.stop();
    return 0;
}
