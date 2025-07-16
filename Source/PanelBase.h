/*
  ==============================================================================

    PanelBase.h
    Created: 16 Jul 2025 10:19:10am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PanelDefines.h"


class Panel : public juce::Component {
    
    public:
    
        Panel(TDN01AudioProcessor* tdnProcessor);
        ~Panel();
        
        void paint(juce::Graphics& g) override;
                  
    protected:
    
        TDN01AudioProcessor* mProcessor;
    
};
