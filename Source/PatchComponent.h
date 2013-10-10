/*
  ==============================================================================

    PatchWindow.h
    Created: 1 Oct 2013 1:09:07pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#ifndef PATCHCOMPONENT_H_INCLUDED
#define PATCHCOMPONENT_H_INCLUDED

#include "PluginProcessor.h"
#include "SeriesDeviceCallBacks.h"




class PatchComponent : public Component
{
public: PatchComponent();
    SeriesDeviceCallBacks sdcb;
   
    void appearance(bool state);
    
    void closeButtonPressed();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatchComponent)

   ScopedPointer<DocumentWindow> docWindow;

};

#endif  // PATCHWINDOW_H_INCLUDED
