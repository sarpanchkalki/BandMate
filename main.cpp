#include "core/engine/AudioEngine.h"
#include "core/engine/ParameterManager.h"
#include "core/engine/WASAPIOutput.h"
#include "core/engine/DroneInstrument.h"
int main() {
    AudioEngine engine;

    MusicalParameters params;
    params.tempoBPM = 72.0f;
    params.energy = 0.6f;
    params.rootFrequency = 261.63f;
    params.scaleType = 0;
    params.mode = PlayMode::FOLLOW;

engine.addInstrument(
    std::make_unique<DroneInstrument>()
);


    engine.setParameters(params);
engine.addInstrument(std::make_unique<DroneInstrument>());
    engine.prepare();

    WASAPIOutput output;
    output.start([&](float* buffer, int frames) {
        engine.render(buffer, frames);
    });

    while (true) {
        Sleep(1000); // keep app alive
    }

    return 0;
}
