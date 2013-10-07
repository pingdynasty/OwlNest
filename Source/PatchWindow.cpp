/*
  ==============================================================================

    PatchWindow.cpp
    Created: 1 Oct 2013 1:09:07pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#include "PatchWindow.h"


PatchWindow ::  PatchWindow() : DocumentWindow("Owl Patch",Colours::lightgrey,DocumentWindow::allButtons)

{
     StompBoxAudioProcessor& stompbox = sdcb.getStompbox();
       setContentOwned (stompbox.createEditor(), true);
    
    centreWithSize (getWidth(), getHeight());
    setVisible (false);
}

void PatchWindow :: appearance(bool state)
{
    if(state == false|| NULL)
    {
    setVisible (false);
    }
    if(state == true)
    {
        setVisible(true);
    }
}

void PatchWindow :: closeButtonPressed()
{
   // JUCEApplication::getInstance()->systemRequestedQuit();
    setVisible (false);
}
