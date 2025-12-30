#ifndef DRONE_INSTRUMENT_H
#define DRONE_INSTRUMENT_H

#include "Instrument.h"

class DroneInstrument : public Instrument {
public:
    DroneInstrument();

    void prepare(const Session& session) override;

    void noteOn(float frequency,
                NoteDuration duration,
                float velocity) override;

    void process(float* output, int frames) override;

    void stop() override;

private:
    float frequency_;
    float velocity_;
    bool active_;
};

#endif
