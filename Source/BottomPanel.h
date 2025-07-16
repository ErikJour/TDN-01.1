/*
  ==============================================================================

    BottomPanel.h
    Created: 16 Jul 2025 10:20:40am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "PanelBase.h"
#include "TDNSlider.h"

class BottomPanel : public Panel {
    
    public:
    
        BottomPanel(TDN01AudioProcessor* tdnProcessor);
        ~BottomPanel();
        
        void paint(juce::Graphics& g) override;
                  
    private:
    
        std::unique_ptr<TDNSlider> globalGainSlider;
    const int sliderSize;;
    
};
