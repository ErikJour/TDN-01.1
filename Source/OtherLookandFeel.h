/*
  ==============================================================================

    OtherLookandFeel.h
    Created: 22 Jul 2025 10:11:36am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class OtherLookAndFeel : public juce::LookAndFeel_V4
{
    
public:
    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height,float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override;

    
    
    
    
};
