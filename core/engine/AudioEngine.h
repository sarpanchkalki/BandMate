#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "Session.h"
#include "Dynamics.h"
#include "Instrument.h"

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
    std::vector<std::unique_ptr<Instrument>> instruments_;
};

#endif
