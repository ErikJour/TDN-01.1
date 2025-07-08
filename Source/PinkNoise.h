/*
  ==============================================================================

    PinkNoise.h
    Created: 8 Jul 2025 2:24:18pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <stddef.h>
#include <JuceHeader.h>

class PinkNoise{
    
public:
    
    PinkNoise();
    PinkNoise(const PinkNoise&) = delete;
    PinkNoise& operator=(const PinkNoise&) = delete;
    void reset();
    float getNextSample();
    
private:
    
    static constexpr int numContributors = 5;
    int contrib[numContributors] {};
    
    long int accum = 0;
    
    juce::Random pinkGen;
    
    static constexpr int pPSUM[numContributors] = {1, 2, 4, 8, 16};

    
    
};
