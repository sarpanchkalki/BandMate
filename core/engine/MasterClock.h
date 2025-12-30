#ifndef MASTER_CLOCK_H
#define MASTER_CLOCK_H

class MasterClock {
public:
    MasterClock();

    void setSampleRate(int sampleRate);
    void setTempo(float bpm);
    void setTimeSignature(int numerator, int denominator);

    void advance(int frames);

    double currentBeat() const;
    double currentBar() const;
    bool isOnBeat(double subdivision) const;
bool isDownbeat() const;

private:
    int sampleRate_;
    float bpm_;
    int numerator_;
    int denominator_;

    long long sampleCounter_;
    double samplesPerBeat_;
};

#endif
