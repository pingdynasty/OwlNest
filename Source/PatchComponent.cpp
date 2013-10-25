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
    
    patchState.setValue(A);
   
        
    dm.addAudioCallback(&sdcb);
    addAndMakeVisible(dualPatchPanel = new DualPatchPanel(sdcb,patchState));
    addAndMakeVisible(transportPanel = new TransportPanel(sdcb));
    
    stompboxBGui = stompboxB.createEditor();
    stompboxAGui = stompboxA.createEditor();
   
    addAndMakeVisible(stompboxBGui);
    addAndMakeVisible(stompboxAGui);
    
    
    addAndMakeVisible(patchButton = new patchModeSwitching(sdcb, patchState));
    
   patchState.addListener(this);
   
 
}


void PatchComponent::valueChanged(Value &patchChange)
{
   /*
    switch((int) patchChange.getValue())
    {
        case A:
        {
            patchState.setValue(A);
            break;
        }
        case B:
        {
            patchState.setValue(B);
            break;
        }
            
            
    }
    */
}


void PatchComponent:: closeButtonPressed()
{
   // JUCEApplication::getInstance()->systemRequestedQuit();
//    setVisible (false);

}
