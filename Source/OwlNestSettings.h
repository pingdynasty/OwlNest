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

#ifdef _MSC_VER
#include <win-util/stdint.h>
#else
#include <stdint.h>
#endif

#include "OpenWareMidiControl.h"
#include "JuceHeader.h"

#define NB_CHANNELS 128 

class OwlNestSettings: public MidiInputCallback, public ApplicationCommandTarget {
 public:
    OwlNestSettings(AudioDeviceManager& dm, Value& updateGui);
    ~OwlNestSettings();
    void loadFromOwl();
    void saveToOwl();
    int getCc(int cc);            // get value of a given cc
    void setCc(int cc,int value);  // set a value for a given cc
    StringArray& getPresetNames(){
      return presets;
    }
    uint64 getLastMidiMessageTime();
    // bool isConnected();
  bool updateFirmware();

  void getCommandInfo(CommandID commandID, ApplicationCommandInfo &result);
  void getAllCommands(Array< CommandID > &commands);
  ApplicationCommandTarget* getNextCommandTarget();
  bool perform(const InvocationInfo& info);
 private:
    int midiArray[NB_CHANNELS]; // index represents Midi CC, value represents Midi Value.
    Value& theUpdateGui;
    AudioDeviceManager& theDm;
    StringArray presets;
    uint64 lastMidiMessageTime;
    void handleIncomingMidiMessage(	MidiInput * 	source,
                              const MidiMessage & 	message
                              )	;
    void handlePresetNameMessage(uint8_t index, const char* name, int size);
    void handleFirmwareVersionMessage(const char* name, int size);
    void handleDeviceIdMessage(uint8_t* data, int size);
    void handleSelfTestMessage(uint8_t data);
};
