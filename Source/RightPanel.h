/*
  ==============================================================================

    RightPanel.h
    Created: 16 Jul 2025 10:20:33am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "PanelBase.h"
#include "TDNSlider.h"
#include "PanelDefines.h"
#include "TDNComboBox.h"
#include "OtherLookandFeel.h"

class RightPanel : public Panel {
    
    public:
    
        RightPanel(TDN01AudioProcessor* tdnProcessor);
        ~RightPanel();
        
        void paint(juce::Graphics& g) override;
                  
    private:
    OtherLookAndFeel otherLookAndFeel;

        std::unique_ptr<TDNSlider> lpCutoffSlider;
        std::unique_ptr<TDNSlider> lpResonanceSlider;
        std::unique_ptr<TDNSlider> hpCutoffSlider;
    
        std::unique_ptr<TDNSlider> envAttackSlider;
        std::unique_ptr<TDNSlider> envDecaySlider;
        std::unique_ptr<TDNSlider> EnvSustainSlider;
        std::unique_ptr<TDNSlider> envReleaseSlider;
    
        std::unique_ptr<juce::Label> envelopeLabel;
        std::unique_ptr<juce::Label> filtersLabel;
        std::unique_ptr<juce::Label> noiseTypeLabel;
    
        std::unique_ptr<TDNComboBox> noiseTypeComboBox;
    
        const int sliderSize;
        const int comboBoxSize;
        juce::Image logo;
    
    std::unique_ptr<TDNSlider> globalGainSlider;
    std::unique_ptr<juce::Label> gainLabel;
    
};
