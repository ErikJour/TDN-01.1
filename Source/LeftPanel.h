/*
  ==============================================================================

    LeftPanel.h
    Created: 16 Jul 2025 10:20:28am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "PanelBase.h"
#include "TDNSlider.h"
#include "PanelDefines.h"

class LeftPanel : public Panel {
    
    public:
    
        LeftPanel(TDN01AudioProcessor* tdnProcessor);
        ~LeftPanel();
        
        void paint(juce::Graphics& g) override;
                  
    private:
    
        

    
};
