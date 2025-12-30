#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "Session.h"
#include "TimeEngine.h"

class AudioEngine {
public:
    AudioEngine();

    void setSession(const Session& session);

    void prepare();
    void process(float* output, int frames);
    void start();
    void stop();

private:
    Session session_;
    TimeEngine timeEngine_;
};

#endif
