#ifndef RHYTHM_ENGINE_H
#define RHYTHM_ENGINE_H

#include <vector>

class RhythmEngine {
public:
    RhythmEngine();

    // Set beats per cycle (e.g. 4 = 4/4, 16 = teentaal)
    void setCycleLength(int beats);

    // Define which beats are active
    void setPattern(const std::vector<int>& pattern);

    // Check if a beat triggers an event
    bool isBeatActive(int beat) const;

private:
    int cycleLength_;
    std::vector<int> activeBeats_;
};

#endif
