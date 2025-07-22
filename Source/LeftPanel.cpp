/*
  ==============================================================================

    LeftPanel.cpp
    Created: 16 Jul 2025 10:20:28am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "LeftPanel.h"



LeftPanel::LeftPanel(TDN01AudioProcessor* tdnProcessor) :
Panel(tdnProcessor),  comboBoxSize(COMBO_BOX_SIZE * .65), sliderSize(SLIDER_SIZE)

{
    
  
    jassert(mProcessor != nullptr);

    setSize(PANEL_LEFT_WIDTH, PANEL_LEFT_HEIGHT);
    
    lfoLabel = std::make_unique<juce::Label>();
    lfoLabel->setBounds((getWidth() - sliderSize) / 2, 10, sliderSize, sliderSize);
    lfoLabel->setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    lfoLabel->setText ("LFO", juce::dontSendNotification);
    lfoLabel->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(*lfoLabel);
    
    lfoSourceComboBox = std::make_unique<TDNComboBox> (mProcessor->apvts, ::ParameterID::lfoSource.getParamID());
    lfoSourceComboBox->setBounds(getWidth() / 2 - comboBoxSize / 2, 70, comboBoxSize, 20);
    lfoSourceComboBox->addItem("Vol", 1);
    lfoSourceComboBox->addItem("LP Cut", 2);
    lfoSourceComboBox->addItem("HP Cut", 3);
    lfoSourceComboBox->setSelectedId(1);
    addAndMakeVisible(lfoSourceComboBox.get());
    
    lfoRateSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::lfoRate.getParamID());
    lfoRateSlider->setBounds(PANEL_LEFT_WIDTH / 2 - sliderSize / 2, getHeight() / 6.25, sliderSize, sliderSize);
    lfoRateSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoRateSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(lfoRateSlider.get());
    
    lfoDepthSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::lfoDepth.getParamID());
    lfoDepthSlider->setBounds(PANEL_LEFT_WIDTH / 2 - sliderSize / 2, getHeight() / 3.5, sliderSize, sliderSize);
    lfoDepthSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoDepthSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(lfoDepthSlider.get());
                        
}

LeftPanel::~LeftPanel()
{
    
}
        
void LeftPanel::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
    
//    g.setColour(juce::Colours::whitesmoke);
//    g.drawFittedText("TDN-01", 22, 0, 100, 50, juce::Justification::centredLeft, 1);
    
    g.setColour(juce::Colours::grey);
    g.drawRect(10, 30, 80, 235);
    
}
                  
  
