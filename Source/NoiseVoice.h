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


struct NoiseVoice
{
    NoiseGenerator noise;
    int note;
    Envelope env;
    


void reset()
{
    note = 0;
    noise.setlevel(0.2f);
    env.reset();
    
}

float render()
{
    float noiseSample = noise.getNextSample();
    float envelope = env.nextValue();
    float output = noiseSample * envelope;
    return output;
}
    
};


