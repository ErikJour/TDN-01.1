/*
  ==============================================================================

    RightPanel.cpp
    Created: 16 Jul 2025 10:20:33am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "RightPanel.h"

RightPanel::RightPanel(TDN01AudioProcessor* tdnProcessor) :
Panel(tdnProcessor), sliderSize(SLIDER_SIZE), comboBoxSize(COMBO_BOX_SIZE)

{
    jassert(mProcessor != nullptr);

    setSize(PANEL_RIGHT_WIDTH, PANEL_RIGHT_HEIGHT);
    
    //NOISE TYPE LABEL
    noiseTypeLabel = std::make_unique<juce::Label>();
    noiseTypeLabel->setBounds(getWidth() / 3, -20, sliderSize, sliderSize);
    noiseTypeLabel->setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    noiseTypeLabel->setText ("Noise Type", juce::dontSendNotification);
    noiseTypeLabel->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(*noiseTypeLabel);
    
    //NOISE TYPE COMBO BOX
    noiseTypeComboBox = std::make_unique<TDNComboBox> (mProcessor->apvts, ::ParameterID::noiseType.getParamID());
    noiseTypeComboBox->setBounds(getWidth() / 2 - comboBoxSize / 2, 40, comboBoxSize, 20);
    noiseTypeComboBox->addItem("White", 1);
    noiseTypeComboBox->addItem("Pink", 2);
    noiseTypeComboBox->setSelectedId(1);

    addAndMakeVisible(noiseTypeComboBox.get());
    
    
    //FILTER LABEL
    filtersLabel = std::make_unique<juce::Label>();
    filtersLabel->setBounds(getWidth() / 3, getHeight() / 6, sliderSize, sliderSize);
    filtersLabel->setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    filtersLabel->setText ("Filters", juce::dontSendNotification);
    filtersLabel->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(*filtersLabel);
    
    //=======================
    
    //FILTER SLIDERS
    lpCutoffSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::lpCutoff.getParamID());
    lpCutoffSlider->setBounds(PANEL_RIGHT_WIDTH / 3.5 - sliderSize / 2, getHeight() / 4, sliderSize, sliderSize);
    lpCutoffSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lpCutoffSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    lpCutoffSlider->setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(lpCutoffSlider.get());
    
    //=======================
    
    lpResonanceSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::lpResonance.getParamID());
    lpResonanceSlider->setBounds(PANEL_RIGHT_WIDTH / 3.5 + sliderSize / 1.33, getHeight() / 4, sliderSize, sliderSize);
    lpResonanceSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lpResonanceSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    lpResonanceSlider->setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(lpResonanceSlider.get());
    
    hpCutoffSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::hpCutoff.getParamID());
    hpCutoffSlider->setBounds(getWidth() / 2 - sliderSize / 2, getHeight() / 4 + sliderSize, sliderSize, sliderSize);
    hpCutoffSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    hpCutoffSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    hpCutoffSlider->setLookAndFeel(&otherLookAndFeel);

    addAndMakeVisible(hpCutoffSlider.get());

    //ENVELOPE LABEL
    envelopeLabel = std::make_unique<juce::Label>();
    envelopeLabel->setBounds(getWidth() / 3, getHeight() / 2 - 10, sliderSize, sliderSize);
    envelopeLabel->setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    envelopeLabel->setText ("Amp Env", juce::dontSendNotification);
    envelopeLabel->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(*envelopeLabel);
    
    
    //ENVELOPE SLIDERS
    envAttackSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::envAttack.getParamID());
    envAttackSlider->setBounds(PANEL_RIGHT_WIDTH / 3.5 - sliderSize / 2, getHeight() / 1.75 - 5, sliderSize, sliderSize);
    envAttackSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    envAttackSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    envAttackSlider->setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(envAttackSlider.get());
    
    envDecaySlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::envDecay.getParamID());
    envDecaySlider->setBounds(PANEL_RIGHT_WIDTH / 3.5 + sliderSize / 1.33, getHeight() / 1.75 - 5, sliderSize, sliderSize);
    envDecaySlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    envDecaySlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    envDecaySlider->setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(envDecaySlider.get());
    
    EnvSustainSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::envSustain.getParamID());
    EnvSustainSlider->setBounds(PANEL_RIGHT_WIDTH / 3.5 - sliderSize / 2, getHeight() / 1.75 + sliderSize * 1.2 - 5, sliderSize, sliderSize);
    EnvSustainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    EnvSustainSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    EnvSustainSlider->setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(EnvSustainSlider.get());
    
    envReleaseSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::envRelease.getParamID());
    envReleaseSlider->setBounds(PANEL_RIGHT_WIDTH / 3.5 + sliderSize / 1.33, getHeight() / 1.75 + sliderSize * 1.2 - 5, sliderSize, sliderSize);
    envReleaseSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    envReleaseSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    envReleaseSlider->setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(envReleaseSlider.get());
    
    //GAIN 
    gainLabel = std::make_unique<juce::Label>();
    gainLabel->setBounds(getWidth() / 2 - sliderSize / 2, 515, sliderSize, sliderSize);
    gainLabel->setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    gainLabel->setText ("Volume", juce::dontSendNotification);
    gainLabel->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(*gainLabel);
    

    globalGainSlider = std::make_unique<TDNSlider> (mProcessor->apvts, ::ParameterID::globalGain.getParamID());
    globalGainSlider->setBounds(getWidth() / 2 - sliderSize / 2, 560, sliderSize, sliderSize);
    globalGainSlider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    globalGainSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    globalGainSlider->setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(globalGainSlider.get());
    
   
                                                     
}

RightPanel::~RightPanel()
{
    
}
        
void RightPanel::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
    
    g.setColour(juce::Colours::grey);
    g.drawRect(20, getHeight() / 2 + 10, 160, 190);
    
    g.setColour(juce::Colours::grey);
    g.drawRect(20, getHeight() / 6 + 20, 160, 180);
    
    g.setColour(juce::Colours::grey);
    g.drawRect(20, 0, 160, 100);

//    logo = juce::ImageCache::getFromMemory(BinaryData::ERIKJOURGENSEN_ICON_B_W_png, BinaryData::ERIKJOURGENSEN_ICON_B_W_pngSize);
//    g.drawImageWithin(logo, getWidth() - 55, 575, 50, 50, juce::RectanglePlacement::stretchToFit);

}
