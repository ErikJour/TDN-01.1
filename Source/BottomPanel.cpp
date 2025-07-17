/*
  ==============================================================================

    BottomPanel.cpp
    Created: 16 Jul 2025 10:20:40am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "BottomPanel.h"


BottomPanel::BottomPanel(TDN01AudioProcessor* tdnProcessor) :
Panel(tdnProcessor), sliderSize(SLIDER_SIZE)

{
    
  
    jassert(mProcessor != nullptr);

    setSize(PANEL_BOTTOM_WIDTH, PANEL_BOTTOM_HEIGHT);
    
    //GAIN LABEL
    gainLabel = std::make_unique<juce::Label>();
    gainLabel->setBounds(22.5, -30, sliderSize, sliderSize);
    gainLabel->setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    gainLabel->setText ("Volume", juce::dontSendNotification);
    gainLabel->setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(*gainLabel);
    

    globalGainSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::globalGain.getParamID());
    globalGainSlider->setBounds(PANEL_LEFT_WIDTH / 2 - sliderSize / 2, getHeight() / 2 - sliderSize / 2, sliderSize, sliderSize);
    globalGainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    globalGainSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(globalGainSlider.get());
    
                                                     
}

BottomPanel::~BottomPanel()
{
    
}
        
void BottomPanel::paint(juce::Graphics& g) 
{
    g.setColour(juce::Colours::black);
    g.fillAll();

}
                  
    
