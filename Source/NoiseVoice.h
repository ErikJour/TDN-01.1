/*
  ==============================================================================

    NoiseVoice.h
    Created: 30 Jun 2025 9:05:21pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include "noiseGenerator.h"


struct NoiseVoice
{
    NoiseGenerator noise;
    int note;


void reset()
{
    note = 0;
    noise.setlevel(0.0f);
    
}

float render()
    {
    float noiseSample = noise.getNextSample();
    return noiseSample;
}
    
};


