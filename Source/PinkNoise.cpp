/*
  ==============================================================================

    PinkNoise.cpp
    Created: 8 Jul 2025 2:24:18pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "PinkNoise.h"

PinkNoise::PinkNoise() { reset(); }

void PinkNoise::reset()
{
    for (int i = 0; i < numContributors; i++) {
        contrib[i] = 0;
    }
    accum = 0;
}

float PinkNoise::getNextSample()
{
    int random = pinkGen.nextInt();
    for (int i = 0; i < numContributors; i++) {
        
        if ((random & pPSUM[i]) != 0)
        {
            accum -= contrib[i];
            contrib[i] = ((pinkGen.nextInt() >> 3) & 0xFFFF) - 32768;
            accum += contrib[i];
        }
    }

    return static_cast<float>(accum) / (numContributors * 32768.0f);
}
