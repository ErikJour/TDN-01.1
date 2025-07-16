/*
  ==============================================================================

    TDNComboBox.h
    Created: 16 Jul 2025 12:20:43pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "JuceHeader.h"

class TDNComboBox
        : public juce::ComboBox
{
    public:
        TDNComboBox(juce::AudioProcessorValueTreeState& APVTS,
                        const juce::String& paramID);
        ~TDNComboBox();
    
    private:
        std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mComboBoxAttachment;
        TDN01AudioProcessor* tdnProcessor;
        
    
    
};
