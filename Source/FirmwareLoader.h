#ifndef FIRMWARELOADER_H_INCLUDED
#define FIRMWARELOADER_H_INCLUDED

#include "JuceHeader.h"

class FirmwareLoader {
public:
  FirmwareLoader();
  bool init(const File& file, const String& options);
  void listDevices();
  bool probeDevices();
  bool openDevice();
  bool connectToDevice();
  bool loadFromDevice();
  bool loadToDevice();
  bool resetDevice();
  bool detachDevice();
  bool closeDevice();
  String getMessage();
  void errx(int errid, const String& msg);
private:
  String message;
};

#endif  // FIRMWARELOADER_H_INCLUDED
