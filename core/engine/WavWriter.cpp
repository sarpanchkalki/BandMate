#include "WavWriter.h"
#include <fstream>
#include <cstdint>
#include <algorithm>

static void writeInt(std::ofstream& file, uint32_t value) {
    file.write(reinterpret_cast<const char*>(&value), 4);
}

static void writeShort(std::ofstream& file, uint16_t value) {
    file.write(reinterpret_cast<const char*>(&value), 2);
}

void WavWriter::writeMono16(
    const std::string& filename,
    const std::vector<float>& samples,
    int sampleRate
) {
    std::ofstream file(filename, std::ios::binary);

    int numSamples = static_cast<int>(samples.size());
    int dataSize = numSamples * sizeof(int16_t);

    // RIFF header
    file.write("RIFF", 4);
    writeInt(file, 36 + dataSize);
    file.write("WAVE", 4);

    // fmt chunk
    file.write("fmt ", 4);
    writeInt(file, 16);
    writeShort(file, 1);        // PCM
    writeShort(file, 1);        // Mono
    writeInt(file, sampleRate);
    writeInt(file, sampleRate * 2);
    writeShort(file, 2);
    writeShort(file, 16);

    // data chunk
    file.write("data", 4);
    writeInt(file, dataSize);

    // audio data
    for (float s : samples) {
        int16_t pcm = static_cast<int16_t>(
            std::clamp(s, -1.0f, 1.0f) * 32767
        );
        file.write(reinterpret_cast<const char*>(&pcm), 2);
    }

    file.close();
}
