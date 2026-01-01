#ifndef FOLLOW_ENGINE_H
#define FOLLOW_ENGINE_H

class FollowEngine {
public:
    FollowEngine();

    void setScaleRoot(float rootFreq);
    void updateInputPitch(float freq);
    int suggestedChordDegree() const;

private:
    float rootFreq_;
    int lastDegree_;
};

#endif
