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
  void resetParameterNames();
  void loadFromOwl();
  void saveToOwl();
  void sendPc(int pc);
  int getCc(int cc);            // get value of a given cc
  void setCc(int cc,int value);  // set a value for a given cc
  int getPc(){            // get value of program change
    return pc;
  }
  StringArray& getPresetNames();
  StringArray& getUserPresetNames();
  StringArray& getFactoryPresetNames();
  StringArray& getParameterNames();
  int getUserPresetStartIndex();
  int getFactoryPresetStartIndex();
  String getFirmwareVersion();
  uint64 getLastMidiMessageTime();
  // bool isConnected();
  bool updateFirmware();
  bool updateBootloader();
  void loadSysexPatchFromDisk();
  void checkForUpdates();
  bool downloadFromServer(CommandID commandID);
  void getCommandInfo(CommandID commandID, ApplicationCommandInfo &result);
  void getAllCommands(Array< CommandID > &commands);
  ApplicationCommandTarget* getNextCommandTarget();
  bool perform(const InvocationInfo& info);
  int getConfigurationValue(const char* name);
  void setConfigurationValue(const char* name, int value);
  void storeFirmware(uint8_t slot);
  void clearMessages(){
    programMessage = "";
    statsMessage = "";
  }
  String getProgramMessage(){
    return programMessage;
  }
  String getStatsMessage(){
    return statsMessage;
  }
private:
  String programMessage;
  String statsMessage;
  bool deviceFirmwareUpdate(const File& file, const String& options);
  int midiArray[NB_CHANNELS]; // index represents Midi CC, value represents Midi Value.
  int pc; // last received Program Change value
  Value& theUpdateGui;
  AudioDeviceManager& theDm;
  StringArray presets;
  StringArray userPresets;
  StringArray factoryPresets;
  StringArray parameters;
  HashMap<String, int> configuration;
  uint64 lastMidiMessageTime;
  String firmwareVersion;
  void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message);
  void handleProgramMessage(const char* name, int size);
  void handleDeviceStatsMessage(const char* name, int size);
  void handlePresetNameMessage(uint8_t index, const char* name, int size);
  void handleParameterNameMessage(uint8_t index, const char* name, int size);
  void handleFirmwareVersionMessage(const char* name, int size);
  void handleDeviceIdMessage(const char* data, int size);
  void handleSelfTestMessage(uint8_t data);
  void handleErrorMessage(uint8_t data);
  void handleSysexConfigurationCommand(const char* name, int size);
};
