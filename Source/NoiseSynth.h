/*
  ==============================================================================

    NoiseSynth.h
    Created: 30 Jun 2025 9:05:10pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include "NoiseVoice.h"
#include "Utils.h"

class NoiseSynth
{
    public:
        NoiseSynth();
    
        void distributeResources(double sampleRate, int samplesPerBlock);
        void releaseResources();
        void reset();
        void render(float** outputBuffers, int sampleCount);
        void midiMessages(uint8_t data0, uint8_t data1, uint8_t data2);
        void startVoice(int note, int velocity);
        void noteOn(int note, int velocity);
        void noteOff(int note);
        
    private:
    
        double sampleRate;
        NoiseVoice voice;
};
