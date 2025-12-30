#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "Session.h"
#include "NoteDuration.h"

// Abstract base class for all instruments
class Instrument {
public:
    virtual ~Instrument() = default;

    // Called once before playback
    virtual void prepare(const Session& session) = 0;

    // Trigger a musical note
    virtual void noteOn(float frequency,
                        NoteDuration duration,
                        float velocity) = 0;

    // Called every audio block (later)
    virtual void process(float* output, int frames) = 0;

    // Stop instrument
    virtual void stop() = 0;
};

#endif
