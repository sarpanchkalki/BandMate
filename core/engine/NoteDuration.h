#ifndef NOTE_DURATION_H
#define NOTE_DURATION_H

// Musical note durations (relative to beat)
enum class NoteDuration {
    WHOLE,      // 4 beats
    HALF,       // 2 beats
    QUARTER,    // 1 beat
    EIGHTH,     // 0.5 beat
    SIXTEENTH   // 0.25 beat
};

// Convert duration to beats
inline float durationToBeats(NoteDuration d) {
    switch (d) {
        case NoteDuration::WHOLE:      return 4.0f;
        case NoteDuration::HALF:       return 2.0f;
        case NoteDuration::QUARTER:    return 1.0f;
        case NoteDuration::EIGHTH:     return 0.5f;
        case NoteDuration::SIXTEENTH:  return 0.25f;
        default: return 1.0f;
    }
}

#endif
