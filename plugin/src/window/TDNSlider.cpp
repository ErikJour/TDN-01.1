/*
  ==============================================================================

    TDNSlider.cpp
    Created: 16 Jul 2025 12:29:56pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "TDNSlider.h"

TDNSlider::TDNSlider(juce::AudioProcessorValueTreeState& APVTS,
                        const juce::String& paramID) : juce::Slider(paramID)
{
    mSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (APVTS, paramID, *this);
}
TDNSlider::~TDNSlider()
{
    
}
