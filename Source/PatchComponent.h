/*
  ==============================================================================

    PatchWindow.h
    Created: 1 Oct 2013 1:09:07pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#ifndef PATCHCOMPONENT_H_INCLUDED
#define PATCHCOMPONENT_H_INCLUDED

#include "StompBoxAudioProcessor.h"
#include "SeriesDeviceCallBacks.h"
#include "TransportPanel.h"
#include "DualPatchPanel.h"
#include "PatchMode.h"
#include "Enums.h"



class PatchComponent : public Component,
                       public Value::Listener


{
public: PatchComponent(AudioDeviceManager& dm);
  
    juce::Value patchState;
    juce::Value owlConfig;
    juce::Value stompAPatch;
    juce::Value stompBPatch;
    juce::Value transportValue;
    
    SeriesDeviceCallBacks sdcb;
    
    void valueChanged(juce::Value &patchChange);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatchComponent);
    ScopedPointer<TransportPanel> transportPanel;
    ScopedPointer<DualPatchPanel> dualPatchPanel;
    ScopedPointer<patchModeSwitching> patchButton;
    ScopedPointer<Component> stompboxAGui;
    ScopedPointer<Component> stompboxBGui;



};

#endif  // PATCHWINDOW_H_INCLUDED
