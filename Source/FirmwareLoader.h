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
  int do_dnload(struct dfu_if *dif, int xfer_size, struct dfu_file *file, ThreadWithProgressWindow& win);
  bool loadFromDevice(ThreadWithProgressWindow& win);
  bool loadToDevice(ThreadWithProgressWindow& win);
  bool resetDevice();
  bool detachDevice();
  bool closeDevice();
  String getMessage();
private:
  void errx(int errid, const String& msg);
  String message;
};

#endif  // FIRMWARELOADER_H_INCLUDED
