/*
  ==============================================================================

    noiseGenerator.cpp
    Created: 30 Jun 2025 9:04:27pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "noiseGenerator.h"


NoiseGenerator::NoiseGenerator() : noiseLevel(0.0f),
                                    amplitude(0.0f)
{
    
}

NoiseGenerator::~NoiseGenerator() 
{
    
}

float NoiseGenerator::getNextSample()
{
    
    float output = (noise.nextFloat() * 2.0f - 1.0f) * noiseLevel * amplitude;
    float reduction = 0.5f;
    return output * reduction;

}

void NoiseGenerator::setAmplitude(float newAmplitude)
{
    
    amplitude = newAmplitude;
    
}

void NoiseGenerator::setlevel(float newNoiseLevel)
{
    
    noiseLevel = newNoiseLevel;
    
}
