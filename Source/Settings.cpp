/*
  ==============================================================================

    Settings.cpp
    Created: 23 Sep 2013 11:34:08am
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#include "Settings.h"

OwlNestSettings::OwlNestSettings(AudioDeviceManager& dm, Value& updateGui):
theDm(dm), theUpdateGui(updateGui)
{
    // init midiArray
    for (int i=0; i<NB_CHANNELS; i++) {
        midiArray[i]=0;
    }
    
    midiArray[60]=64; // test
    midiArray[32]=69; // test
    
    // Add midi Input Callback
    theDm.addMidiInputCallback("",this);
}


void OwlNestSettings::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message)	{
    midiArray[message.getControllerNumber()]=message.getControllerValue();
    int i=theUpdateGui.getValue();
    theUpdateGui.setValue(1-i); // change the updateGui Value to update GUI
}

OwlNestSettings::~OwlNestSettings(){
}

void OwlNestSettings::setCc(int cc,int value)
{
    // check value range
    int v=value;
    if (v<0) {
        v=0;
    }
    else if (v>=NB_CHANNELS) {
        v=NB_CHANNELS-1;
    }
    // set midiArray and update Owl
    if (cc>0 && cc<NB_CHANNELS){
        midiArray[cc]=v;
        theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,cc,v));
    }
}

int OwlNestSettings::getCc(int cc)
{
    if (cc>0 && cc<NB_CHANNELS){
        return midiArray[cc];
    }
    else{
        return -1;
    }
}

void OwlNestSettings::SaveToOwl(){
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,SAVE_SETTINGS,127));
}

void OwlNestSettings::LoadFromOwl(){
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,REQUEST_SETTINGS,127)); // Will provoke incoming midi messages
}
