#ifndef TIME_ENGINE_H
#define TIME_ENGINE_H

class TimeEngine {
public:
    TimeEngine();

    void setTempo(float bpm);

    void update(float deltaSeconds);

    int getBeatCount() const;

    // NEW: get duration in seconds
    float beatsToSeconds(float beats) const;

private:
    float secondsPerBeat_;
    float accumulator_;
    int beatCount_;
};

#endif
