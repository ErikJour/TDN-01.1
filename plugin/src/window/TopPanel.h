/*
  ==============================================================================

    TopPanel.h
    Created: 16 Jul 2025 10:43:56am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "PanelBase.h"
#include "TDNSlider.h"
#include "PanelDefines.h"

class TopPanel : public Panel {
    
    public:
    
        TopPanel(TDN01AudioProcessor* tdnProcessor);
        ~TopPanel();
        
        void paint(juce::Graphics& g) override;
                  
    private:
    
        

    
};
