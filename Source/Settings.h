/*
  ==============================================================================

    Settings.h
    Created: 23 Sep 2013 11:34:25am
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#endif  // SETTINGS_H_INCLUDED

#include "OpenWareMidiControl.h"
#include "JuceHeader.h"

#define NB_CHANNELS 128 

class OwlNestSettings: public MidiInputCallback {
    public:
    OwlNestSettings(AudioDeviceManager& dm, Value& updateGui);
    ~OwlNestSettings();
    void LoadFromOwl();
    void SaveToOwl();
    int getCc(int cc);            // get value of a given cc
    void setCc(int cc,int value);  // set a value for a given cc
    
    private:
    int midiArray[NB_CHANNELS]; // index represents Midi CC, value represents Midi Value.
    Value& theUpdateGui;
    AudioDeviceManager& theDm;
    void handleIncomingMidiMessage(	MidiInput * 	source,
                              const MidiMessage & 	message
                              )	;
};
