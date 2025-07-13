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
    juce::WebSliderRelay webGlobalGainRelay;
    
    //Webview GUI
    juce::WebBrowserComponent webViewGui;
    
    //WEB PARAMETER ATTACHMENTS
    juce::WebToggleButtonParameterAttachment webNoiseTypeParameterAttachment;
    juce::WebSliderParameterAttachment webGlobalGainParameterAttachment;
    
    //JUCE Sliders / Attachments
    juce::Slider ampEnvAttackSlider;
    juce::Slider ampEnvDecaySlider;
    juce::Slider ampEnvSustainSlider;
    juce::Slider ampEnvReleaseSlider;
    juce::Slider masterGainSlider;
    juce::ComboBox noiseTypeComboBox;
    
    juce::Label nameLabel{"TDN-01"};
    juce::Label envLabel{"Amp Env"};
    juce::Label filterLabel{"Filters"};
    juce::Label globalGainLabel{"Global Gain"};
   
    
    using APVTS = juce::AudioProcessorValueTreeState;
    
    using SliderAttachment = APVTS::SliderAttachment;
    
    SliderAttachment ampEnvAttackAmount {audioProcessor.apvts,
                                        ParameterID::envAttack.getParamID(),
                                        ampEnvAttackSlider};
    
    SliderAttachment ampEnvDecayAmmount {audioProcessor.apvts,
                                        ParameterID::envDecay.getParamID(),
                                        ampEnvDecaySlider};
    
    SliderAttachment ampEnvSustainAmount {audioProcessor.apvts,
                                        ParameterID::envSustain.getParamID(),
                                        ampEnvSustainSlider};
    
    SliderAttachment ampEnvReleaseAmount {audioProcessor.apvts,
                                        ParameterID::envRelease.getParamID(),
                                        ampEnvReleaseSlider};
    
    SliderAttachment globalGainAmount {audioProcessor.apvts,
                                        ParameterID::masterGain.getParamID(),
                                        masterGainSlider};
    
//    using ComboBoxAttachment = APVTS::


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TDN01AudioProcessorEditor)
};
