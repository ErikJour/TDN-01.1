/*
  ==============================================================================

    BottomPanel.cpp
    Created: 16 Jul 2025 10:20:40am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "BottomPanel.h"


BottomPanel::BottomPanel(TDN01AudioProcessor* tdnProcessor) :
Panel(tdnProcessor)

{
    
  
    jassert(mProcessor != nullptr);

    setSize(PANEL_BOTTOM_WIDTH, PANEL_BOTTOM_HEIGHT);
    

    
    
                                                     
}

BottomPanel::~BottomPanel()
{
    
}
        
void BottomPanel::paint(juce::Graphics& g) 
{
    g.setColour(juce::Colours::black);
    g.fillAll();
    
   
}
                  
    
