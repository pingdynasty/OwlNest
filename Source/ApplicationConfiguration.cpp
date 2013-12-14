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
    if(!properties->containsKey("presetdirectory"))
      properties->setValue("presetdirectory", File::getSpecialLocation(File::userDocumentsDirectory)
			   .getChildFile(opts.applicationName).getFullPathName());
    if(!properties->containsKey("midioutput"))
      properties->setValue("midioutput", "OWL FS");
    if(!properties->containsKey("midiinput"))
      properties->setValue("midiinput", "OWL FS");
    if(!properties->isValidFile())
      std::cerr << "Invalid properties file: " << properties->getFile().getFullPathName() << std::endl;
  }
  return properties;
}

File ApplicationConfiguration::getPresetDirectory(){
  PropertiesFile* properties = getApplicationProperties();
  File dir(properties->getValue("presetdirectory"));
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
