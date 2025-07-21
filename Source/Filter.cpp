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

    updateSmoothers();
    return processSample(x, 0);
}