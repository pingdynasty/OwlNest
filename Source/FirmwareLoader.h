#ifndef FIRMWARELOADER_H_INCLUDED
#define FIRMWARELOADER_H_INCLUDED

#include "JuceHeader.h"

class FirmwareLoader {
public:
  int updateFirmware(File& file, const String& options);
};

#endif  // FIRMWARELOADER_H_INCLUDED
