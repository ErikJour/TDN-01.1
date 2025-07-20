/*
  ==============================================================================

    Filter.cpp
    Created: 30 Jun 2025 9:04:17pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "Filter.h"

void Filter::updateCoefficients(float cutoff, float resonance)
{
   /* g = std::tan(PI * cutoff / sampleRate);

    k = 1.0f / resonance;

    a1 = 1.0f / (1.0f + g * (g + k));

    a2 = g * a1;
     
    a3 = g * a2;*/

    setCutoffFrequencyHz(cutoff);
    setResonance(std::clamp(resonance / 30.0f, 0.0f, 1.0f));

}

void Filter::reset()
{
    g = 0.0f;
    k = 0.0f;
    a1 = 0.0f;
    a2 = 0.0f;
    a3 = 0.0f;

    ic1eq = 0.0f;
    ic2eq = 0.0f;
}

float Filter::render(float x)
{
    /*float v3 = x - ic2eq;

    float v1 = a1 * ic1eq + a2 * v3;

    float v2 = ic2eq + a2 * ic1eq + a3 * v3;

    ic1eq = 2.0f * v1 - ic1eq;

    ic2eq = 2.0f * v2 - ic2eq;

    return v2;*/

    updateSmoothers();
    return processSample(x, 0);
}