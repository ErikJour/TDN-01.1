/*
  ==============================================================================

    NoiseVoice.h
    Created: 30 Jun 2025 9:05:21pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include "noiseGenerator.h"
#include "Envelope.h"
#include "LFO.h"
#include "PinkNoise.h"


struct NoiseVoice
{
    NoiseGenerator noise;
    PinkNoise pinkNoise;
    int note;
    Envelope env;
    LFO lfo;


void reset()
{
    note = 0;
    noise.setlevel(0.2f);
    env.reset();
    lfo.reset();
    
}

float render()
{
    float noiseSample = noise.getNextSample();
//    float pinkNoiseSample = pinkNoise.getNextSample();
    float envelope = env.nextValue();
    float modulated = lfo.getNextSample();
    float modulatedSample = modulated * noiseSample;
//    float modulatedSample = modulated * pinkNoiseSample;

    float output = modulatedSample * envelope;
    return output;
    
}
    
};


