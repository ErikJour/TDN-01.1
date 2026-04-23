/*
  ==============================================================================

    TDNComboBox.cpp
    Created: 16 Jul 2025 12:20:43pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "TDNComboBox.h"


TDNComboBox::TDNComboBox(juce::AudioProcessorValueTreeState& APVTS,
                        const juce::String& paramID) : juce::ComboBox(paramID)
{
    mComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (APVTS, paramID, *this);
}
TDNComboBox::~TDNComboBox()
{
    
}
    


