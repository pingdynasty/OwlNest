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
    StompBoxAudioProcessor& stompboxA = sdcb.getStompboxA();
    StompBoxAudioProcessor& stompboxB = sdcb.getStompboxB();
    
    
        
    dm.addAudioCallback(&sdcb);
    addAndMakeVisible(dualPatchPanel = new DualPatchPanel(sdcb));
    addAndMakeVisible(transportPanel = new TransportPanel(sdcb));
    
    stompboxBGui = stompboxB.createEditor();
    stompboxAGui = stompboxA.createEditor();
   
    addAndMakeVisible(stompboxBGui);
    addAndMakeVisible(stompboxAGui);
    
    
    addAndMakeVisible(patchButton = new patchModeSwitching(sdcb));
    
   
 
}



void PatchComponent:: closeButtonPressed()
{
   // JUCEApplication::getInstance()->systemRequestedQuit();
//    setVisible (false);

}
