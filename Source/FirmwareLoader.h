#ifndef FIRMWARELOADER_H_INCLUDED
#define FIRMWARELOADER_H_INCLUDED

#include "JuceHeader.h"

class FirmwareLoader {
public:
  int updateFirmware(File& file);
  int updateBootloader(File& file);
};

#endif  // FIRMWARELOADER_H_INCLUDED
