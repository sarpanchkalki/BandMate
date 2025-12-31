#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "Session.h"
#include "Dynamics.h"
#include "Instrument.h"
#include "MasterClock.h"
#include "Metronome.h"
#include "RhythmEngine.h"
#include "HarmonyEngine.h"
#include "EnergyEngine.h"


#include <memory>
#include <vector>

class AudioEngine {
public:
    AudioEngine();

    void setSession(const Session& session);
    void addInstrument(std::unique_ptr<Instrument> instrument);

    void prepare();
    void render(float* output, int frames);

private:
    Session session_;
    Dynamics dynamics_;
    MasterClock clock_;
Metronome metronome_;
RhythmEngine rhythm_;
HarmonyEngine harmony_;
EnergyEngine energy_;


    std::vector<std::unique_ptr<Instrument>> instruments_;
};

#endif
