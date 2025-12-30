#include "core/engine/AudioEngine.h"
#include "core/engine/DroneInstrument.h"

int main() {
    Session session;
    session.mode = Mode::FOLLOW;
    session.tempo = 60.0f;
    session.energy = 0.6f;
    session.key.rootFrequency = 261.63f;
    session.key.scale = ScaleType::MAJOR;

    AudioEngine engine;
    engine.setSession(session);

    engine.addInstrument(std::make_unique<DroneInstrument>());

    engine.prepare();
    engine.start();

    engine.stop();
    return 0;
}
