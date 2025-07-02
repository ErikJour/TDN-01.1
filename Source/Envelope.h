/*
  ==============================================================================

    Envelope.h
    Created: 30 Jun 2025 9:04:10pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once

const float SILENCE = 0.0001f;

class Envelope
{
    public:
        float nextValue();
        void reset();
        inline bool isActive() const { return level > SILENCE; }
        inline bool isInAttack() const {  return target >= 2.0f; }
        void attack();
        void release();
        
        float level;
        float attackMultiplier;
        float decayMultiplier;
        float sustainLevel;
        float releaseMultiplier;
    
    private:
        float multiplier;
        float target;
};
