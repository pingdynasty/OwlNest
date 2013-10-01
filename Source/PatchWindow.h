/*
  ==============================================================================

    PatchWindow.h
    Created: 1 Oct 2013 1:09:07pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#ifndef PATCHWINDOW_H_INCLUDED
#define PATCHWINDOW_H_INCLUDED

#include "PluginProcessor.h"


class PatchWindow : public DocumentWindow
{
public: PatchWindow(StompBoxAudioProcessor& stompbox);

    void closeButtonPressed();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatchWindow)
};

#endif  // PATCHWINDOW_H_INCLUDED
