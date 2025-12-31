#ifndef ENERGY_ENGINE_H
#define ENERGY_ENGINE_H

class EnergyEngine {
public:
    EnergyEngine();

    void setBaseEnergy(float energy); // 0.0 – 1.0
    void advance(int frames);
    float value() const;

private:
    float baseEnergy_;
    float phase_;
    float currentEnergy_;
};

#endif
