/*
  ==============================================================================

    OtherLookandFeel.cpp
    Created: 22 Jul 2025 10:11:36am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "OtherLookandFeel.h"

void OtherLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height,
                    float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider)
{
    float knobScale = 0.75f; 

    float diameter = juce::jmin(width, height) * knobScale;
    float radius = diameter / 2;
    
    float centerX = x + width / 2;
    float centerY = y + height / 2;
    
    float rx = centerX - radius;
    float ry = centerY - radius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
    
    
    juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
    

    g.fillEllipse(dialArea);
    
    g.setColour(juce::Colours::whitesmoke);
    
    juce::Path dialTick;
    float tickWidth = 4.0f;
    float tickLength = radius * 0.6f;
    dialTick.addRectangle(-tickWidth / 2.0f, -tickLength, tickWidth, tickLength);
    
    g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
    
    g.setColour(juce::Colours::whitesmoke);
    g.drawEllipse(rx, ry, diameter, diameter, 4.0f);
    
}
