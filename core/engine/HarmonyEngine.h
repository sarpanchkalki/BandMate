#ifndef HARMONY_ENGINE_H
#define HARMONY_ENGINE_H

class HarmonyEngine {
public:
    HarmonyEngine();

    void setRootFrequency(float root);
    void triggerBar();
    void process(float* output, int frames);
void setChordDegree(int degree);
bool prepared_ = false;


private:
    float rootFreq_;
    int chordIndex_;
    float phase_[3];
};

#endif
