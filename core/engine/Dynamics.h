#ifndef DYNAMICS_H
#define DYNAMICS_H

class Dynamics {
public:
    explicit Dynamics(float energy = 0.5f);

    void setEnergy(float energy);

    // Returns velocity multiplier (0.0 – 1.0)
    float velocity() const;

private:
    float energy_;
};

#endif
