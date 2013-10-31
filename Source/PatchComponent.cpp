/*
  ==============================================================================

    PatchWindow.cpp
    Created: 1 Oct 2013 1:09:07pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#include "PatchComponent.h"


PatchComponent ::  PatchComponent(AudioDeviceManager& dm) : Component("Patch"), sdcb(patchState,owlConfig,stompAPatch,stompBPatch, transportValue)

{
 
    
    StompBoxAudioProcessor& stompboxA = sdcb.getStompboxA();
    StompBoxAudioProcessor& stompboxB = sdcb.getStompboxB();
    
    patchState.setValue(A);
    owlConfig.setValue(SINGLE);
    stompAPatch.setValue(stompboxA.getCurrentPatchName());
    stompBPatch.setValue(stompboxB.getCurrentPatchName());
    
        
    dm.addAudioCallback(&sdcb);
    addAndMakeVisible(dualPatchPanel = new DualPatchPanel(stompboxA.getPatchNames(),patchState,owlConfig,stompAPatch,stompBPatch));
    addAndMakeVisible(transportPanel = new TransportPanel(sdcb,transportValue));
    
    stompboxBGui = stompboxB.createEditor();
    stompboxAGui = stompboxA.createEditor();

    addAndMakeVisible(stompboxBGui);
    addAndMakeVisible(stompboxAGui);
    
    
    addAndMakeVisible(patchButton = new patchModeSwitching(sdcb, patchState));
    
    patchState.addListener(this);
    transportValue.addListener(this);
   
 
}


void PatchComponent::valueChanged(Value &valueChange)
{
   if(valueChange == patchState)
   {
    switch((int) patchState.getValue())
    {
        case A:
        {
            
            stompboxAGui->toFront(true);
            patchButton->toFront(true);
            break;
        }
        case B:
        {
            stompboxBGui->toFront(true);
            patchButton->toFront(true);
            break;
        }
            
            
    }
   }
    else if (valueChange == transportValue)
    {
        if(transportValue == PREPAREFILEMODE)
        {
            
            sdcb.setInputFile(transportPanel->getTestFile());
//            transportValue.setValue(FILEMODE);
        }
    }
    
}



