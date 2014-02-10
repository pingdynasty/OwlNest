/*
  ==============================================================================

    ApplicationCommands.h
    Created: 14 Dec 2013 9:49:35pm
    Author:  Martin

  ==============================================================================
*/

#ifndef APPLICATIONCOMMANDS_H_INCLUDED
#define APPLICATIONCOMMANDS_H_INCLUDED

namespace ApplicationCommands {
enum ApplicationCommands {
  updateFirmware = 0x2001,
  updateBootloader = 0x2002,
  checkForFirmwareUpdates = 0x2003,
  checkForBootloaderUpdates = 0x2004
};
}

#endif  // APPLICATIONCOMMANDS_H_INCLUDED
