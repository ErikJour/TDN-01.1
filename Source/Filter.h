/*
  ==============================================================================

    Filter.h
    Created: 30 Jun 2025 9:04:17pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once

#pragma once
#include <cmath>
#include <JuceHeader.h>


class Filter : public juce::dsp::LadderFilter<float>

{
public:
    float sampleRate;

    void updateCoefficients(float cutoff, float resonance);
    void reset();
    float render(float x);

private:
    const float PI = 3.1415926535897932f;
    float g, k, a1, a2, a3;
    float ic1eq, ic2eq;
};
