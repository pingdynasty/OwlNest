#ifndef FIRMWARELOADER_H_INCLUDED
#define FIRMWARELOADER_H_INCLUDED

#include "JuceHeader.h"

class FirmwareLoader {
public:
  FirmwareLoader();
  int updateFirmware(const File& file, const String& options);
  String getMessage();
  void errx(int errid, const String& msg);
private:
  String message;
};

#endif  // FIRMWARELOADER_H_INCLUDED
