/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TDN01AudioProcessorEditor::TDN01AudioProcessorEditor (TDN01AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    webViewGui{juce::WebBrowserComponent::Options{}}
{
    addAndMakeVisible(webViewGui);
    juce::String localServer = "http://localhost:5173/";
    webViewGui.goToURL(localServer);
    setSize (800, 600);
}

TDN01AudioProcessorEditor::~TDN01AudioProcessorEditor()
{
}

//==============================================================================


void TDN01AudioProcessorEditor::resized()
{
    webViewGui.setBounds(getLocalBounds());
}
