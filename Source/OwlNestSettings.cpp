/*
  ==============================================================================

    Settings.cpp
    Created: 23 Sep 2013 11:34:08am
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#include <iomanip>
#include <sysex.h>
#include <stdio.h>
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
  firmwareVersion="";
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

String OwlNestSettings::getFirmwareVersion(){
    return firmwareVersion;
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
	if(message.getSysExDataSize() > 4)
	  handleErrorMessage(data[4]);
	break;
      }
      }
    }
  }
  if(hasChanged)
    theUpdateGui.setValue(!(bool)theUpdateGui.getValue());
}

void OwlNestSettings::handleFirmwareVersionMessage(const char* name, int size){
  String str(name, size);
  firmwareVersion = str;
#ifdef DEBUG
  std::cout << "Device Firmware: " << str << std::endl;
#endif // DEBUG
  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Device Firmware", "Currently installed: "+str);
        // AlertWindow alert("Firmware version currently installed:", theSettings.getFirmwareVersion(), juce::AlertWindow::InfoIcon);
        // alert.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
        // alert.runModalLoop();
  
}

void OwlNestSettings::handleDeviceIdMessage(uint8_t* data, int size){
#ifdef DEBUG
  std::cout << "Device ID: 0x";
  for(int i=0; i<size; ++i)
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)data[i];
  std::cout << std::endl;
#endif // DEBUG
}

void OwlNestSettings::handleErrorMessage(uint8_t data){
#ifdef DEBUG
  if(data == 0)
    std::cout << "Error status 0: OK" << std::endl;
  else
    std::cout << "Error status " << data << ": " << strerror(data) << std::endl;
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

class DeviceFirmwareUpdateTask  : public ThreadWithProgressWindow {
private:
  const File& file;
  const String& options;
  FirmwareLoader loader;
public:
  DeviceFirmwareUpdateTask(const File& theFile, const String& theOptions)    
    : ThreadWithProgressWindow ("Device Firmware Update", true, true),
      file(theFile), options(theOptions) {}
  // DeviceFirmwareUpdateTask()
  //   : ThreadWithProgressWindow ("Device Firmware Update", true, false) {}

  void error(const String& msg){
    setStatusMessage(msg);
    loader.closeDevice();
    while(!threadShouldExit())
      Thread::sleep(100);
  }

  void run() {
    setProgress(0.0);
    setStatusMessage("Connecting to device");

    if(threadShouldExit())
      return;

    if(!loader.init(file, options))
      return error(loader.getMessage());

    setProgress(0.02);
    setStatusMessage("Probing for DFU device");

    bool detected = loader.probeDevices();
    for(int i=0; i<40 && ! detected; ++i){
      Thread::sleep(100);
      setProgress(0.02+i*0.14/40);
      detected = loader.probeDevices();
      if(threadShouldExit())
	return error("Cancelled!");
    }

    if(!detected)
      return error("Could not find a connected DFU device");

    setProgress(0.16);
    setStatusMessage("Opening device");
    if(!loader.openDevice())
      return error(loader.getMessage());
    setProgress(0.18);
    setStatusMessage("Connecting to device");
    if(!loader.connectToDevice())
      return error(loader.getMessage());
    setProgress(0.2);

    if(threadShouldExit())
      return error("Cancelled!");

    setStatusMessage("Downloading binary image to device");
    if(!loader.loadToDevice(*this))
      return error(loader.getMessage());
    setProgress(0.85);

    setStatusMessage("Detaching device");
    if(!loader.detachDevice())
      setStatusMessage(loader.getMessage()); // continue
    setProgress(0.90);

    // setStatusMessage("Resetting device");
    // if(!loader.resetDevice())
    //   setStatusMessage(loader.getMessage()); // continue
    // //   return error(loader.getMessage());
    // setProgress(0.95);

    setStatusMessage("Closing device");
    if(!loader.closeDevice())
      return error(loader.getMessage());
    setProgress(1.0);

    setStatusMessage("Update complete");
  }
};

bool OwlNestSettings::deviceFirmwareUpdate(const File& file, const String& options){
  // put device into DFU mode
  setCc(DEVICE_FIRMWARE_UPDATE, 127);
  DeviceFirmwareUpdateTask task(file, options);
  if(task.runThread()){
    AlertWindow alert("Success", "Device Update Complete. Please reboot your OWL and relaunch OwlNest.", juce::AlertWindow::InfoIcon);
    alert.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
    alert.runModalLoop();
    return true;
  }else{
    AlertWindow alert("Cancelled", "Device Update Cancelled", juce::AlertWindow::WarningIcon);
    alert.addButton("Continue", 1, juce::KeyPress(), juce::KeyPress());
    alert.runModalLoop();
    return false;
  }
}

bool OwlNestSettings::updateBootloader(){
  DBG("Update bootloader");
  AlertWindow alert("Update Bootloader", 
		    "Updating the bootloader can brick your OWL! Are you sure you want to proceed?", 
		    juce::AlertWindow::WarningIcon);
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

bool OwlNestSettings::downloadFromServer(CommandID commandID) {
    String nodeString, optionString, warningString;
    PropertySet* props = ApplicationConfiguration::getApplicationProperties();
    switch (commandID){
    case ApplicationCommands::checkForFirmwareUpdates:
      warningString = "Beware that this procedure can make your OWL unresponsive!";
      nodeString = "firmwares";
      optionString = props->getValue("firmware-dfu-options");
      break;
    case ApplicationCommands::checkForBootloaderUpdates:
      warningString = "Beware that this procedure can brick your OWL!";
      nodeString = "bootloaders";
      optionString = props->getValue("bootloader-dfu-options");
      break;
    default:
      return false;
    }
    
    String xmlFilename ("updates.xml");
    URL url(props->getValue("owl-updates-dir-url")+xmlFilename);
    ScopedPointer<XmlElement> xmlUpdates;
    if(url.isWellFormed())
      xmlUpdates = url.readEntireXmlStream(0);
    if(xmlUpdates == NULL) {
      AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Connection Error", "Server connection failed");
      return false;
    }
    XmlElement* filesNode = xmlUpdates->getChildByName(nodeString);
    StringArray names;
    XmlElement* child = filesNode->getFirstChildElement();
    while(child != nullptr){
      names.add(child->getStringAttribute("name"));
      child = child->getNextElement();
    }
    AlertWindow popup("Download File From Server", "Choose file:", juce::AlertWindow::InfoIcon);
    popup.addButton("Cancel", 0, juce::KeyPress(), juce::KeyPress());
    popup.addButton("Download", 1, juce::KeyPress(), juce::KeyPress());
    popup.addComboBox("box", names);
    if(popup.runModalLoop()==0)
      return false;
    popup.setVisible(false);
    String selectedFilename(popup.getComboBoxComponent("box")->getText());
    URL fwUrl(props->getValue("owl-updates-dir-url")+selectedFilename);
    ScopedPointer<InputStream> strm;
    strm = fwUrl.createInputStream(0);
    if(strm == NULL){
      AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Connection Error", "File unavailable", "Continue");
      return false;
    }
    File theTargetFile(ApplicationConfiguration::getApplicationDirectory().getChildFile(selectedFilename));
    FileChooser chooser("Save As", theTargetFile, "*.bin");
    bool succeeded = false;
    if(!chooser.browseForFileToSave(true))
      return false;
    theTargetFile = chooser.getResult();
    TemporaryFile temp (theTargetFile);
    ScopedPointer<FileOutputStream> out(temp.getFile().createOutputStream());
    if(out != nullptr) {
      out->writeFromInputStream(*strm, strm->getTotalLength());
      out = nullptr; // deletes the stream
      succeeded = temp.overwriteTargetFileWithTemporary();
    }
    if(!succeeded){
      AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "File Error", "Failed to save file", "Continue");
      return false;
    }
    if(AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "Update Device", 
				    "Would you like to update your OWL with this binary now? "+warningString, "Yes", "No"))
    {
        DBG("pathName"<< theTargetFile.getFullPathName());
        DBG("optionString " << optionString);
        return deviceFirmwareUpdate(theTargetFile, optionString);
    }
    return true;
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
    result.setInfo("Update Device Firmware from File", String::empty, String::empty, 0);
    break;
  case ApplicationCommands::updateBootloader:
    result.setInfo("Update Device Bootloader from File", String::empty, String::empty, 0);
    break;
  case ApplicationCommands::checkForFirmwareUpdates:
    result.setInfo("Download Firmware from Server", String::empty, String::empty, 0);
    break;
  case ApplicationCommands::checkForBootloaderUpdates:
    result.setInfo("Download Bootloader from Server", String::empty, String::empty, 0);
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
    downloadFromServer(info.commandID);
    break;
  case ApplicationCommands::checkForBootloaderUpdates:
    downloadFromServer(info.commandID);
    break;
  }
  return true;
}

ApplicationCommandTarget* OwlNestSettings::getNextCommandTarget(){
  return NULL;
}
