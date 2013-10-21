/*
  ==============================================================================

    PatchWindow.cpp
    Created: 1 Oct 2013 1:09:07pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#include "PatchComponent.h"


PatchComponent ::  PatchComponent(AudioDeviceManager& dm) : Component("Patch")

{
    StompBoxAudioProcessor& stompbox = sdcb.getStompbox();
     
     addAndMakeVisible( stompbox.createEditor());

     dm.addAudioCallback(&sdcb);
   
   // docWindow = new DocumentWindow("Application Settings", Colours::lightgrey,0);
   // docWindow->setContentNonOwned(applicationSettings, true);
   //docWindow->setVisible(true);
    
    
   
 //   centreWithSize (getWidth(), getHeight());
   // setVisible (false);
}

void PatchComponent:: appearance(bool state)
{
    if(state == false|| NULL)
    {
  //  setVisible (false);
    docWindow->setVisible(false);
    docWindow->toFront(true);
    }
    if(state == true)
    {
    //    setVisible(true);
        docWindow->setVisible(true);
    }
}

void PatchComponent:: closeButtonPressed()
{
   // JUCEApplication::getInstance()->systemRequestedQuit();
//    setVisible (false);
appearance(false); 
}
