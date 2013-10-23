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

class PatchComponent : public Component {
public: 
  PatchComponent(AudioDeviceManager& dm);
private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatchComponent)
  SeriesDeviceCallBacks sdcb;
  ScopedPointer<Component> editor;
};

#endif  // PATCHWINDOW_H_INCLUDED
