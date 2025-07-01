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
        void midiMessages(__UINT8_TYPE__ data0, __UINT8_TYPE__ data1, __UINT8_TYPE__ data2);
        void startVoice(int note, int velocity);
        void noteOn(int note, int velocity);
        void noteOff(int note);
        
    private:
    
        double sampleRate;
        NoiseVoice voice;
};
