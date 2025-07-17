/*
  ==============================================================================

    LeftPanel.cpp
    Created: 16 Jul 2025 10:20:28am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "LeftPanel.h"


LeftPanel::LeftPanel(TDN01AudioProcessor* tdnProcessor) :
Panel(tdnProcessor)

{
    
  
    jassert(mProcessor != nullptr);

    setSize(PANEL_LEFT_WIDTH, PANEL_LEFT_HEIGHT);
    
                        
}

LeftPanel::~LeftPanel()
{
    
}
        
void LeftPanel::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
    
    g.setColour(juce::Colours::whitesmoke);
    g.drawFittedText("TDN-01", 22, 0, 100, 50, juce::Justification::centredLeft, 1);
    
}
                  
  
