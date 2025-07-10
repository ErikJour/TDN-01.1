/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TDN01AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TDN01AudioProcessorEditor (TDN01AudioProcessor&);
    ~TDN01AudioProcessorEditor() override;

    //==============================================================================
    void resized() override;

private:
    
    //Resource for UI file
    using Resource = juce::WebBrowserComponent::Resource;
    
    std::optional<Resource> getResource(const juce::String& url);
    
    //Audio processor reference
    TDN01AudioProcessor& audioProcessor;
    
    //RELAYS
    juce::WebToggleButtonRelay webNoiseTypeRelay;
    
    //Webview GUI
    juce::WebBrowserComponent webViewGui;
    
    //WEB PARAMETER ATTACHMENTS
    juce::WebToggleButtonParameterAttachment webNoiseTypeParameterAttachment;
    
    //JUCE Sliders / Attachments
    juce::Slider ampEnvAttackSlider;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    
    using SliderAttachment = APVTS::SliderAttachment;
    
    SliderAttachment ampEnvAttackAmount {audioProcessor.apvts,
                                        ParameterID::envAttack.getParamID(),
                                        ampEnvAttackSlider};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TDN01AudioProcessorEditor)
};
