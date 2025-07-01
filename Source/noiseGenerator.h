/*
  ==============================================================================

    noiseGenerator.h
    Created: 30 Jun 2025 9:04:27pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class NoiseGenerator
{
    
public:
    
    enum class NoiseType { white, pink, brown };
    
    NoiseGenerator();
    ~NoiseGenerator();
    
    float getNextSample();
    void setAmplitude(float newAmplitude);
    void setlevel(float newNoiseLevel);
    
private:
    
    juce::Random noise;
    float noiseLevel;
    float amplitude;
    
};
