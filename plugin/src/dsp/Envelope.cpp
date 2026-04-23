/*
  ==============================================================================

    Envelope.cpp
    Created: 30 Jun 2025 9:04:10pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "Envelope.h"

float Envelope::nextValue() 
{
    level = multiplier * (level - target) + target;
    
    if (level + target > 3.0f) {
        
        multiplier = decayMultiplier;
        target = sustainLevel;
    }
    
    return level;
}

void Envelope::reset()
{
    level = 0.0f;
    target = 0.0f;
    multiplier = 0.0f;
}

void Envelope::attack()
{
    level += SILENCE + SILENCE;
    target = 2.0f;
    multiplier = attackMultiplier;
}

void Envelope::release()
{
    target = 0.0f;
    multiplier = releaseMultiplier;
    
}
