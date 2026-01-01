#ifndef PITCH_DETECTOR_H
#define PITCH_DETECTOR_H

class PitchDetector {
public:
    PitchDetector();

    void process(const float* input, int frames);
    float detectedFrequency() const;

private:
    float lastFrequency_;
};

#endif
