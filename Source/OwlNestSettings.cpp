/*
  ==============================================================================

    Settings.cpp
    Created: 23 Sep 2013 11:34:08am
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#include <iomanip>
#include <sysex.h>
#include "OwlNestSettings.h"
#include "OpenWareMidiControl.h"
#include "FirmwareLoader.h"
#include "ApplicationCommands.h"
#include "ApplicationConfiguration.h"

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

StringArray& OwlNestSettings::getPresetNames(){
  return presets;
}

StringArray& OwlNestSettings::getParameterNames(){
  return parameters;
}

void OwlNestSettings::handlePresetNameMessage(uint8_t index, const char* name, int size){
  presets.set(index, String(name, size));
}

void OwlNestSettings::handleParameterNameMessage(uint8_t index, const char* name, int size){
  parameters.set(index, String(name, size));
}

void OwlNestSettings::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message){
  lastMidiMessageTime = Time::currentTimeMillis();
  bool hasChanged = false;
  if(message.isController()){
    midiArray[message.getControllerNumber()]=message.getControllerValue();
    hasChanged = true;
  }else if(message.isSysEx() && message.getSysExDataSize() > 2){
    const uint8 *data = message.getSysExData();
    if(data[0] == MIDI_SYSEX_MANUFACTURER && data[1] == MIDI_SYSEX_DEVICE){
      switch(data[2]){
      case SYSEX_PRESET_NAME_COMMAND: {
	handlePresetNameMessage(data[3], (const char*)&data[4], message.getSysExDataSize()-4);
	// hasChanged = true;
	break;
      }
      case SYSEX_PARAMETER_NAME_COMMAND: {
	handleParameterNameMessage(data[3], (const char*)&data[4], message.getSysExDataSize()-4);
	hasChanged = true;
	break;
      }
      case SYSEX_FIRMWARE_VERSION: {
	handleFirmwareVersionMessage((const char*)&data[3], message.getSysExDataSize()-3);
	break;
      }
      case SYSEX_DEVICE_ID: {
		#if JUCE_MAC
			int len = message.getSysExDataSize()-3;
			uint8_t deviceId[len];
			len = sysex_to_data((uint8_t*)(data+3), deviceId, len);
			handleDeviceIdMessage(deviceId, len);
		#endif
		break;
      }
      case SYSEX_SELFTEST:{
	handleSelfTestMessage(data[3]);
	break;
      }
      }
    }
  }
  if(hasChanged)
    theUpdateGui.setValue(!(bool)theUpdateGui.getValue());
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

void OwlNestSettings::handleSelfTestMessage(uint8_t data){
#ifdef DEBUG
  if(data & 0x01)
    std::cout << "Preset stored in FLASH" << std::endl;
  else
    std::cout << "Preset not stored in FLASH" << std::endl;
  std::cout << ((data & 0x02) ? "PASSED" : "FAILED") << " Memory test" << std::endl;
  std::cout << ((data & 0x04) ? "PASSED" : "FAILED") << " External 8MHz oscillator" << std::endl;
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

uint64 OwlNestSettings::getLastMidiMessageTime(){
    return lastMidiMessageTime;
}

bool OwlNestSettings::deviceFirmwareUpdate(const File& file, const String& options){
  // put device into DFU mode
  setCc(DEVICE_FIRMWARE_UPDATE, 127);
  FirmwareLoader loader;
  if(loader.updateFirmware(file, options) == 0)
    return true;
  String msg("Firmware update failed with message:\n");
  msg += loader.getMessage();
  AlertWindow warning("Bootloader Update Error", msg, juce::AlertWindow::WarningIcon);
  warning.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
  warning.runModalLoop();
  return false;
}

bool OwlNestSettings::updateBootloader(){
  DBG("Update bootloader");
  AlertWindow alert("Update Bootloader", 
		    "Updating the bootloader can brick your OWL! Are you sure you want to proceed?", 
		    juce::AlertWindow::InfoIcon);
  alert.addButton("Cancel", 0, juce::KeyPress(), juce::KeyPress());
  alert.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
  if(alert.runModalLoop() == 1){
    alert.setVisible(false);
    FileChooser chooser("Select Bootloader", ApplicationConfiguration::getApplicationDirectory(), "*.bin");
    if(chooser.browseForFileToOpen()){
      File file = chooser.getResult();
      PropertySet* props = ApplicationConfiguration::getApplicationProperties();
      String options = props->getValue("bootloader-dfu-options");
      return deviceFirmwareUpdate(file, options);
    }
  }
  return false;
}

bool OwlNestSettings::updateFirmware(){
  DBG("Update firmware!");
  AlertWindow alert("Update Firmware", 
		    "Changing the firmware can make your OWL unresponsive! Are you sure you want to proceed?", 
		    juce::AlertWindow::InfoIcon);
  alert.addButton("Cancel", 0, juce::KeyPress(), juce::KeyPress());
  alert.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
  if(alert.runModalLoop() == 1){
    alert.setVisible(false);
    FileChooser chooser("Select Firmware", ApplicationConfiguration::getApplicationDirectory(), "*.bin");
    if(chooser.browseForFileToOpen()){
      PropertySet* props = ApplicationConfiguration::getApplicationProperties();
      String options = props->getValue("firmware-dfu-options");
      File file = chooser.getResult();
      return deviceFirmwareUpdate(file, options);
    }
  }
  return false;
}

bool OwlNestSettings::updateFirmwareFromXml(){
    PropertySet* props = ApplicationConfiguration::getApplicationProperties();
    String xmlFilename ("updates.xml");
    URL url(props->getValue("owl-updates-dir-url")+xmlFilename);
    XmlElement* xmlUpdates = nullptr;
    if(url.isWellFormed())
    {
        xmlUpdates = url.readEntireXmlStream(0);
    }
    if (xmlUpdates==nullptr)
    {
        AlertWindow warning("Connection Error", "Server Connection failed.", juce::AlertWindow::WarningIcon);
        warning.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
        warning.runModalLoop();
        return false;
    }

    AlertWindow alert("Warning",
                          "Beware that this procedure can make your OWL unresponsive!",
                          juce::AlertWindow::InfoIcon);
    alert.addButton("Cancel", 0, juce::KeyPress(), juce::KeyPress());
    alert.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
    if (alert.runModalLoop() == 0)
        return false;
    else
    {
        XmlElement* firmwares = xmlUpdates->getChildByName("firmwares");
        StringArray names;
        XmlElement* child = firmwares->getFirstChildElement();
        while (child != nullptr)
        {
            names.add(child->getStringAttribute("name"));
            child = child->getNextElement();
        }
        AlertWindow popup("Select",
                          "Choose file:",
                          juce::AlertWindow::InfoIcon);
        popup.addButton("Cancel", 0, juce::KeyPress(), juce::KeyPress());
        popup.addButton("Update", 1, juce::KeyPress(), juce::KeyPress());
        popup.addComboBox("box", names);
        if (popup.runModalLoop()==0)
            return false;
        else
        {
            String selectedFilename(popup.getComboBoxComponent("box")->getText());
            URL fwUrl(props->getValue("owl-updates-dir-url")+selectedFilename);
            InputStream* strm = fwUrl.createInputStream(0);
            File fw(props->getValue("application-directory")+selectedFilename);
            if (fw.exists())
                fw.deleteFile();
            fw.createOutputStream()->writeFromInputStream(*strm, strm->getTotalLength());
        }
    }
}

bool OwlNestSettings::updateBootloaderFromXml(){
    PropertySet* props = ApplicationConfiguration::getApplicationProperties();
    URL url(props->getValue("owl-updates-dir-url"));
    XmlElement* xmlUpdates = nullptr;
    if(url.isWellFormed())
    {
        xmlUpdates = url.readEntireXmlStream(0);
    }
    if (xmlUpdates==nullptr)
    {
        AlertWindow warning("Connection Error", "Server Connection failed.", juce::AlertWindow::WarningIcon);
        warning.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
        warning.runModalLoop();
        return false;
    }
    
    AlertWindow alert("Warning",
                      "Beware that this procedure can brick your OWL!",
                      juce::AlertWindow::InfoIcon);
    alert.addButton("Cancel", 0, juce::KeyPress(), juce::KeyPress());
    alert.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
    if (alert.runModalLoop() ==0)
        return false;
    else
    {
        XmlElement* bootloaders = xmlUpdates->getChildByName("bootloaders");
        StringArray names;
        XmlElement* child = bootloaders->getFirstChildElement();
        while (child != nullptr)
        {
            names.add(child->getStringAttribute("name"));
            child = child->getNextElement();
        }
        AlertWindow popup("Select",
                          "Choose file:",
                          juce::AlertWindow::InfoIcon);
        popup.addButton("Cancel", 0, juce::KeyPress(), juce::KeyPress());
        popup.addButton("Update", 1, juce::KeyPress(), juce::KeyPress());
        popup.addComboBox("box", names);
        popup.runModalLoop();
    }
}

void OwlNestSettings::getAllCommands(Array<CommandID> &commands){
  commands.add(ApplicationCommands::updateFirmware);
  commands.add(ApplicationCommands::updateBootloader);
  commands.add(ApplicationCommands::checkForFirmwareUpdates);
  commands.add(ApplicationCommands::checkForBootloaderUpdates);
}

void OwlNestSettings::getCommandInfo(CommandID commandID, ApplicationCommandInfo &result){
  switch(commandID){
  case ApplicationCommands::updateFirmware:
    result.setInfo("Update Firmware", String::empty, String::empty, 0);
    break;
  case ApplicationCommands::updateBootloader:
    result.setInfo("Update Bootloader", String::empty, String::empty, 0);
    break;
  case ApplicationCommands::checkForFirmwareUpdates:
    result.setInfo("Check for Firmware Updates", String::empty, String::empty, 0);
    break;
  case ApplicationCommands::checkForBootloaderUpdates:
      result.setInfo("Check for Bootloader Updates", String::empty, String::empty, 0);
      break;
  }
}

void OwlNestSettings::checkForUpdates(){
//  PropertySet* props = ApplicationConfiguration::getApplicationProperties();
//  URL url(props->getValue("owl-updates-url"));
//  if(url.isWellFormed())
//    url.launchInDefaultBrowser();
//    OwlNestSettings::updateFromXml();
}

bool OwlNestSettings::perform(const InvocationInfo& info){
  switch(info.commandID){
  case ApplicationCommands::updateFirmware:
    updateFirmware();
    break;
  case ApplicationCommands::updateBootloader:
    updateBootloader();
    break;
  case ApplicationCommands::checkForFirmwareUpdates:
    updateFirmwareFromXml();
    break;
  case ApplicationCommands::checkForBootloaderUpdates:
    updateBootloaderFromXml();
    break;
  }
  return true;
}

ApplicationCommandTarget* OwlNestSettings::getNextCommandTarget(){
  return NULL;
}
