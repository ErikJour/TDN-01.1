/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BottomPanel.h"
#include "LeftPanel.h"
#include "TopPanel.h"
#include "RightPanel.h"
#include "PanelDefines.h"

//==============================================================================
/**
*/
class TDN01AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    TDN01AudioProcessorEditor (TDN01AudioProcessor&);
    ~TDN01AudioProcessorEditor() override;

    //==============================================================================
    void resized() override;
    void timerCallback() override;
    void sendEnvelopeValue(float newValue);

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
    
    juce::ComboBox noiseTypeComboBox;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    
    using SliderAttachment = APVTS::SliderAttachment;
        
    //PANELS
    std::unique_ptr<BottomPanel> bottomMenu;
    std::unique_ptr<LeftPanel> leftMenu;
    std::unique_ptr<TopPanel> topMenu;
    std::unique_ptr<RightPanel> rightMenu;
    
    float envValue {0.0f};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TDN01AudioProcessorEditor)
};
