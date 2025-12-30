#ifndef MUSIC_THEORY_H
#define MUSIC_THEORY_H

#include <vector>

// Supported scales
enum class ScaleType {
    MAJOR,
    MINOR,
    PENTATONIC,
    RAGA_YAMAN,
    RAGA_BHAIRAVI
};

// Musical key / pitch center
struct Key {
    float rootFrequency;   // Sa / Key
    ScaleType scale;
};

// Returns semitone intervals for a scale
inline std::vector<int> getScaleIntervals(ScaleType scale) {
    switch (scale) {
        case ScaleType::MAJOR:
            return {0, 2, 4, 5, 7, 9, 11};
        case ScaleType::MINOR:
            return {0, 2, 3, 5, 7, 8, 10};
        case ScaleType::PENTATONIC:
            return {0, 3, 5, 7, 10};
        case ScaleType::RAGA_YAMAN:
            return {0, 2, 4, 6, 7, 9, 11};   // Tivra Ma
        case ScaleType::RAGA_BHAIRAVI:
            return {0, 1, 3, 5, 7, 8, 10};
        default:
            return {};
    }
}

#endif
