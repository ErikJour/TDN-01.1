/*
  ==============================================================================

    TDNSlider.h
    Created: 16 Jul 2025 12:29:56pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "JuceHeader.h"

class TDNSlider
        : public juce::Slider
{
    public:
        TDNSlider(juce::AudioProcessorValueTreeState& APVTS,
                        const juce::String& paramID);
        ~TDNSlider();
    
    private:
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSliderAttachment;
        TDN01AudioProcessor* tdnProcessor;
        
    
    
};
