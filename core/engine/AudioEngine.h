#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "Session.h"
#include "TimeEngine.h"
#include "Dynamics.h"
#include "RhythmEngine.h"
#include "Instrument.h"

#include <memory>
#include <vector>

class AudioEngine {
public:
    AudioEngine();

    void setSession(const Session& session);

    void addInstrument(std::unique_ptr<Instrument> instrument);

    void prepare();
    void process(float* output, int frames);

    void start();
    void stop();

private:
    Session session_;
    TimeEngine timeEngine_;
    Dynamics dynamics_;
    RhythmEngine rhythm_;

    std::vector<std::unique_ptr<Instrument>> instruments_;
};

#endif
