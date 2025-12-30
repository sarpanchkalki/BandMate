#ifndef METRONOME_H
#define METRONOME_H

class Metronome {
public:
    Metronome();

    void trigger(bool strong);
    void process(float* output, int frames);

private:
    int remainingSamples_;
float accentLevel_;
};

#endif
