/*
  ==============================================================================

    LFO.cpp
    Created: 30 Jun 2025 9:05:30pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "LFO.h"

LFO::LFO() : mSampleRate(44100.0), phase(0.0f), rate(0.0f), depth(0.0f)
{
    reset();
}

LFO::~LFO()
{
}

void LFO::reset()
{
    phase = 0.0f;
}

void LFO::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
    smoothedDepth.reset(inSampleRate, 0.05);
}

void LFO::setRate(float newRate)
{
    rate = newRate;
}

void LFO::setDepth(float newDepth)
{
    smoothedDepth.setTargetValue(newDepth);
}

float LFO::getNextSample()
{
    jassert(mSampleRate > 0.0f);
    
    const float lfoRate = juce::jmap(rate, 0.0f, 1.0f, 0.1f, 20.0f);
    const float phaseIncrement = lfoRate / static_cast<float>(mSampleRate);
    float lfoValue = std::sin(phase * twoPi);
    float currentDepth = smoothedDepth.getNextValue();
    phase += phaseIncrement;
    
    if (phase >= 1.0f)
    {
        phase -= 1.0f;
    }
    
    lfoValue = (lfoValue + 1.0f) * 0.5f;
    float modulated = (1.0f - currentDepth) * 1.0f + currentDepth * lfoValue;
    return modulated;
    
}
