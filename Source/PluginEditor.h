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
    
    TDN01AudioProcessor& audioProcessor;
    
    juce::WebBrowserComponent webViewGui;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TDN01AudioProcessorEditor)
};
