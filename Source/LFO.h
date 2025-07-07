/*
  ==============================================================================

    LFO.h
    Created: 30 Jun 2025 9:05:30pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LFO
{
public:
    static constexpr float twoPi = static_cast<float>(6.28318530718);
    LFO();
    ~LFO();
    
    void reset();
    void setSampleRate(double inSampleRate);
    void setRate(float newRate);
    void setDepth(float newDepth);
    float getNextSample();
    
private:
    double mSampleRate;
    float phase;
    float rate;
    float depth;
    juce::SmoothedValue<float> smoothedDepth;
    
};
