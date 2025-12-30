#ifndef SESSION_H
#define SESSION_H

#include "MusicTheory.h"

enum class Mode {
    FOLLOW,
    LEAD,
    CO_CREATE
};

struct Session {
    Mode mode;

    float tempo;     // BPM
    float energy;    // 0.0 – 1.0

    Key key;         // Musical pitch + scale
};

#endif
