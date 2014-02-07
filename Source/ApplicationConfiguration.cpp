#include "ApplicationConfiguration.h"
#include "JuceHeader.h"

void ApplicationConfiguration::initialise(){
  PropertiesFile* properties = ApplicationConfiguration::getApplicationProperties();
  // getMidiMessageReceiver()->setMidiInput(properties->getValue("midiinput"));
  // getBlipSim()->setMidiOutput(properties->getValue("midioutput"));
}

static PropertiesFile* properties = NULL;
PropertiesFile* ApplicationConfiguration::getApplicationProperties(){
  if(properties == NULL){
    PropertiesFile::Options opts;
    opts.osxLibrarySubFolder = "Application Support";
    opts.folderName = "RebelTechnology";
    opts.applicationName = "OwlNest";
    opts.filenameSuffix = ".properties";
    properties = new PropertiesFile(opts);
    if(!properties->containsKey("application-directory"))
      properties->setValue("application-directory", File::getSpecialLocation(File::userDocumentsDirectory)
			   .getChildFile(opts.applicationName).getFullPathName());
    if(!properties->containsKey("midi-output"))
      properties->setValue("midi-output", "OWL FS");
    if(!properties->containsKey("midi-input"))
      properties->setValue("midi-input", "OWL FS");
    if(!properties->containsKey("bootloader-dfu-options"))
      properties->setValue("bootloader-dfu-options", "0x8000000:leave");
    if(!properties->containsKey("firmware-dfu-options"))
      properties->setValue("firmware-dfu-options", "0x8008000:leave");
    if(!properties->containsKey("owl-updates-url"))
      properties->setValue("owl-updates-url", "http://hoxtonowl.com/software/updates");
      if(!properties->containsKey("owl-updates-list-url"))
          properties->setValue("owl-updates-list-url", "http://hoxtonowl.com/wp-content/uploads/updates.xml");
    if(!properties->isValidFile())
      std::cerr << "Invalid properties file: " << properties->getFile().getFullPathName() << std::endl;
  }
  return properties;
}

File ApplicationConfiguration::getApplicationDirectory(){
  PropertySet* properties = getApplicationProperties();
  File dir(properties->getValue("application-directory"));
  if(!dir.exists())
    dir.createDirectory();
  return dir;
}

void ApplicationConfiguration::release(){
/*     If you're leaking, it's probably because you're using old-fashioned, non-RAII techniques for */
/*     your object management. Tut, tut. Always, always use ScopedPointers, OwnedArrays, */
/*     ReferenceCountedObjects, etc, and avoid the 'delete' operator at all costs! */
  if(properties != NULL)
    properties->saveIfNeeded();
  deleteAndZero(properties);
}
