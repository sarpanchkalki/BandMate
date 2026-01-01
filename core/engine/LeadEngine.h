#ifndef LEAD_ENGINE_H
#define LEAD_ENGINE_H

class LeadEngine {
public:
    LeadEngine();

    void reset();
    void advance(double currentBar);

    int   currentChordDegree() const;
    float currentEnergy() const;

private:
    int   chordDegree_;
    int   lastBar_;
    float energy_;

    void nextChord();
};

#endif
