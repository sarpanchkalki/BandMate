#ifndef WAV_WRITER_H
#define WAV_WRITER_H

#include <string>
#include <vector>

class WavWriter {
public:
    static void writeMono16(
        const std::string& filename,
        const std::vector<float>& samples,
        int sampleRate
    );
};

#endif
