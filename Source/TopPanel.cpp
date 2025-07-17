/*
  ==============================================================================

    TopPanel.cpp
    Created: 16 Jul 2025 10:43:56am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "TopPanel.h"

TopPanel::TopPanel(TDN01AudioProcessor* tdnProcessor) :
Panel(tdnProcessor)

{
    
  
    jassert(mProcessor != nullptr);

    setSize(PANEL_TOP_WIDTH, PANEL_TOP_HEIGHT);
    
                                                     
}

TopPanel::~TopPanel()
{
    
}
        
void TopPanel::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();

}
