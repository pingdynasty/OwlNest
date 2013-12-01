/*
  ==============================================================================

    Settings.cpp
    Created: 23 Sep 2013 11:34:08am
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#include <iomanip>
#include "OwlNestSettings.h"
#include "sysex.h"
#include "OpenWareMidiControl.h"

OwlNestSettings::OwlNestSettings(AudioDeviceManager& dm, Value& updateGui):
theDm(dm), theUpdateGui(updateGui)
{
  memset(midiArray, 0, NB_CHANNELS);
  theDm.addMidiInputCallback(String::empty, this);
  lastMidiMessageTime=0;
}

OwlNestSettings::~OwlNestSettings(){
  theDm.removeMidiInputCallback(String::empty, this);
}

void OwlNestSettings::handlePresetNameMessage(uint8_t index, const char* name, int size){
  presets.set(index, String(name, size));
}

void OwlNestSettings::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message){
  bool hasChanged = false;
  if(message.isController())
  {
    midiArray[message.getControllerNumber()]=message.getControllerValue();
    hasChanged = true;
    // to check connexion status:
      if (message.getControllerNumber()==LED) {
          lastMidiMessageTime=Time::getApproximateMillisecondCounter();
      }
  }
  else if(message.isSysEx() && message.getSysExDataSize() > 2)
  {
    const uint8 *data = message.getSysExData();
    if(data[0] == MIDI_SYSEX_MANUFACTURER && data[1] == MIDI_SYSEX_DEVICE)
    {
      switch(data[2])
        {
            case SYSEX_PRESET_NAME_COMMAND:
                handlePresetNameMessage(data[3], (const char*)&data[4], message.getSysExDataSize()-4);
                hasChanged = true;
                break;
            case SYSEX_FIRMWARE_VERSION:
                handleFirmwareVersionMessage((const char*)&data[3], message.getSysExDataSize()-3);
                break;
            case SYSEX_DEVICE_ID:
                int len = message.getSysExDataSize()-3;
                uint8_t deviceId[len];
                len = sysex_to_data((uint8_t*)(data+3), deviceId, len);
                handleDeviceIdMessage(deviceId, len);
                break;
        }
    }
  }
  if(hasChanged)
  {
    theUpdateGui.setValue(!(bool)theUpdateGui.getValue());
  }
}

void OwlNestSettings::handleFirmwareVersionMessage(const char* name, int size){
#ifdef DEBUG
  String str(name, size);
  std::cout << "OWL: " << str << std::endl;
#endif // DEBUG
}

void OwlNestSettings::handleDeviceIdMessage(uint8_t* data, int size){
#ifdef DEBUG
  std::cout << "Device ID: 0x";
  for(int i=0; i<size; ++i)
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)data[i];
  std::cout << std::endl;
#endif // DEBUG
}

void OwlNestSettings::setCc(int cc,int value)
{
    // check value range
  value = std::min(NB_CHANNELS-1, std::max(0, value));
    // set midiArray and update Owl
    if (cc>0 && cc<NB_CHANNELS){
      midiArray[cc] = value;
      if(theDm.getDefaultMidiOutput() != NULL)
        theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,cc,value));
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

void OwlNestSettings::saveToOwl(){
  if(theDm.getDefaultMidiOutput() != NULL)
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,SAVE_SETTINGS,127));
}

void OwlNestSettings::loadFromOwl(){
  if(theDm.getDefaultMidiOutput() != NULL){
    presets.clear();
    theDm.getDefaultMidiOutput()->sendMessageNow(MidiMessage::controllerEvent(1,REQUEST_SETTINGS,127)); // Will provoke incoming midi messages
  }
}

uint32 OwlNestSettings::getLastMidiMessageTime(){
    return lastMidiMessageTime;
}
