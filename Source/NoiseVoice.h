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
#include "Filter.h"


struct NoiseVoice
{
    NoiseGenerator noise;
    PinkNoise pinkNoise;
    int note;
    Envelope env;
    LFO lfo;
    int noiseType;
    Filter lowPassFilter;
    Filter highPassFilter;

  

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
    pinkNoiseSample *= 0.35f;
    whiteNoiseSample *= 1.5f;
    float envelope = env.nextValue();
//    float modulated = lfo.getNextSample();
    
    float output = 0.0f;

    //White Noise
    if (noiseType == 0) {
        
        output = whiteNoiseSample;
        
    } else if (noiseType == 1) {
        
    output = pinkNoiseSample;

    }
//    float modulatedSample = modulated * noiseSample;
//    float modulatedSample = modulated * pinkNoiseSample;

    //NEW, And MOVED ENVELOPE BELOW (FROM NOISE SAMPLE IF STATEMENTS EARLIER)
    output = lowPassFilter.render(output);
    output = highPassFilter.render(output);


    return output * envelope;
    
}

void updateLPFilter(float cutoff, float resonance)
{
    lowPassFilter.updateCoefficients(cutoff, resonance);
}

void updateHPFilter(float cutoff)
{
    float resonance = 0.0f;
    highPassFilter.updateCoefficients(cutoff, resonance);
}
    
};


