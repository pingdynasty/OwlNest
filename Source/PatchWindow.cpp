/*
  ==============================================================================

    PatchWindow.cpp
    Created: 1 Oct 2013 1:09:07pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#include "PatchWindow.h"

PatchWindow ::  PatchWindow(StompBoxAudioProcessor& stompbox) : DocumentWindow("Owl Patch",Colours::lightgrey,DocumentWindow::allButtons)

{
    setContentOwned (stompbox.createEditor(), true);
    
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

void PatchWindow :: closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
