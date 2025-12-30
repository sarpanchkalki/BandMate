#include "core/engine/AudioEngine.h"
#include "core/engine/DroneInstrument.h"
#include "core/engine/WASAPIOutput.h"
#include "core/engine/AudioConfig.h"

int main() {
    Session session;
    session.tempo = 60;
    session.energy = 0.7f;
    session.key.rootFrequency = 261.63f;

    AudioEngine engine;
    engine.setSession(session);
    engine.addInstrument(std::make_unique<DroneInstrument>());
    engine.prepare();

    WASAPIOutput output;
    output.init(SAMPLE_RATE, 256);

    output.start([&](float* buffer, int frames) {
        engine.render(buffer, frames);
    });

    return 0;
}
