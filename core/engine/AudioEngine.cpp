#include "AudioEngine.h"
#include <cstring>
#include <iostream>
#include <cmath>


AudioEngine::AudioEngine()
    : dynamics_(0.5f) {}

void AudioEngine::setSession(const Session& session) {
    session_ = session;
session_.key.rootFrequency = params_.current().rootFrequency;


    dynamics_.setEnergy(session_.energy);

    const auto& p = params_.current();

    clock_.setTempo(p.tempoBPM);
    energy_.setBaseEnergy(p.energy);
    harmony_.setRootFrequency(p.rootFrequency);
    follow_.setScaleRoot(p.rootFrequency);

    // mic input intentionally disabled
}

void AudioEngine::setParameters(const MusicalParameters& params) {
    params_.setParameters(params);
    setSession(session_);
}

void AudioEngine::addInstrument(std::unique_ptr<Instrument> instrument) {
    instruments_.push_back(std::move(instrument));
}

void AudioEngine::prepare() {
    for (auto& i : instruments_) {
        i->prepare(session_);
    }

if (session_.key.rootFrequency <= 0.0f) return;


    if (!instruments_.empty()) {
        instruments_[0]->noteOn(
            session_.key.rootFrequency,
            NoteDuration::WHOLE,
            dynamics_.velocity()
        );
    }
} // ✅ prepare() CLOSED CORRECTLY


void AudioEngine::render(float* output, int frames) {
if (frames <= 0 || output == nullptr) return;
    std::memset(output, 0, frames * sizeof(float));

    // advance master clock
    clock_.advance(frames);

    energy_.advance(frames);
    float energy = energy_.value();

    bool downbeat = clock_.isDownbeat();

    // FOLLOW → HARMONY (bar-based)
    static int lastHarmonyBar = -1;
    int currentBar = static_cast<int>(clock_.currentBar());

    if (currentBar != lastHarmonyBar) {
        int degree = follow_.suggestedChordDegree();
        harmony_.setChordDegree(degree);
        lastHarmonyBar = currentBar;

// --- TEMP AUDIO PROBE (DO NOT DELETE YET) ---
static float testPhase = 0.0f;
const float testFreq = 440.0f;
const float sampleRate = 48000.0f;

for (int i = 0; i < frames; ++i) {
    float testTone = 0.15f * sinf(testPhase);
    testPhase += 2.0f * 3.1415926535f * testFreq / sampleRate;
    if (testPhase > 2.0f * 3.1415926535f)
        testPhase -= 2.0f * 3.1415926535f;

    output[i] += testTone;  // MIX, not overwrite
}
// --- END TEMP AUDIO PROBE ---


    }

if (params_.current().mode == PlayMode::LEAD) {
    lead_.advance(clock_.currentBar());

    int degree = lead_.currentChordDegree();
    harmony_.setChordDegree(degree);

    energy_.setBaseEnergy(
        lead_.currentEnergy()
    );

    // MAP DEGREE → FREQUENCY (simple, musical)
    float root = session_.key.rootFrequency;
    float ratios[] = {
        1.0f,   // I
        1.125f, // II
        1.25f,  // III
        1.333f, // IV
        1.5f,   // V
        1.667f, // VI
        1.875f  // VII
    };

    float freq = root * ratios[(degree - 1) % 7];

    if (!instruments_.empty()) {
        instruments_[0]->setFrequency(freq);
    }
}


    // TEMP: simulate melodic intent (Sa → Ma → Pa → Sa)
    static int phraseStep = 0;
    static int lastPhraseBar = -1;

    int bar = static_cast<int>(clock_.currentBar());
    if (bar != lastPhraseBar) {
        phraseStep = (phraseStep + 1) % 4;
        lastPhraseBar = bar;
    }

    float ratios[] = {1.0f, 1.33f, 1.5f, 1.0f};
    float fakePitch = session_.key.rootFrequency * ratios[phraseStep];
    follow_.updateInputPitch(fakePitch);

    // trigger beat events
    static bool lastBeatState = false;
    bool onBeat = clock_.isOnBeat(1.0);

    if (onBeat && !lastBeatState) {
        metronome_.trigger(downbeat);
        rhythm_.triggerBeat(downbeat);
    }
    lastBeatState = onBeat;

    // process instruments
    for (auto& i : instruments_) {
        i->process(output, frames);
    }

if (frames > 0) {
if (rhythm_.prepared_) rhythm_.process(output, frames);
if (harmony_.prepared_) harmony_.process(output, frames);
if (metronome_.prepared_) metronome_.process(output, frames);

}


    // subtle accent on downbeat
    if (downbeat) {
        for (int i = 0; i < frames; ++i) {
            output[i] *= 1.05f;
        }
    }

    // add metronome click
    metronome_.process(output, frames);

    // master gain + hard safety clamp
    float masterGain = 0.4f + 0.4f * energy;

    for (int i = 0; i < frames; ++i) {
        output[i] *= masterGain * 0.6f;
        if (output[i] > 1.0f) output[i] = 1.0f;
        if (output[i] < -1.0f) output[i] = -1.0f;
    }
}
