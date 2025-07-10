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
    int noiseType;
  


void reset()
{
    note = 0;
    noise.setlevel(0.2f);
    env.reset();
    lfo.reset();
    
}

float render()
{
    float whiteNoiseSample = noise.getNextSample();
    float pinkNoiseSample = pinkNoise.getNextSample();
    pinkNoiseSample *= 0.5f;
    float envelope = env.nextValue();
//    float modulated = lfo.getNextSample();
    
    float output = 0.0f;
    
    
    //White Noise
    if (noiseType == 0) {
        
        output = whiteNoiseSample * envelope;
        
    } else if (noiseType == 1) {
        
        output = pinkNoiseSample * envelope;

    }
//    float modulatedSample = modulated * noiseSample;
//    float modulatedSample = modulated * pinkNoiseSample;

    return output;
    
}
    
};


