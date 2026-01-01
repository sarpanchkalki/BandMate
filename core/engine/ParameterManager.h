#ifndef PARAMETER_MANAGER_H
#define PARAMETER_MANAGER_H

enum class PlayMode {
    NEUTRAL,
    FOLLOW,
    LEAD
};

struct MusicalParameters {
    float tempoBPM;
    float energy;
    float rootFrequency;
    int   scaleType; // 0 = major (for now)
    PlayMode mode;
};

class ParameterManager {
public:
    ParameterManager();

    void setParameters(const MusicalParameters& params);
    const MusicalParameters& current() const;

private:
    MusicalParameters params_;
};

#endif
