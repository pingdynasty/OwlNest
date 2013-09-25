/*
  ==============================================================================

    OpenWareMidiControl.h
    Created: 23 Sep 2013 12:56:24pm
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#ifndef OPENWAREMIDICONTROL_H_INCLUDED
#define OPENWAREMIDICONTROL_H_INCLUDED

/*
 MIDI Control Change Mappings
*/

enum OpenWareMidiControl {
  LEFT_INPUT_GAIN =        32, /* left channel input gain, -34.5dB to +12dB (92 = 0dB) */
  RIGHT_INPUT_GAIN =       33,
  LEFT_OUTPUT_GAIN =       34, /* left channel output gain, -73dB to +6dB (121 = 0dB) */
  RIGHT_OUTPUT_GAIN =      35,
  LEFT_INPUT_MUTE =        36, /* mute left input (127=muted) */
  RIGHT_INPUT_MUTE =       37,
  LEFT_OUTPUT_MUTE =       38, /* mute left output (127=muted) */
  RIGHT_OUTPUT_MUTE =      39,
  BYPASS =                 40, /* codec bypass mode (127=bypass) */

  SAMPLING_RATE =          60, /* sampling rate
				  0-31 = 8kHz
				  32-63 = 32kHz
				  64-95 = 48kHz
				  96-127 = 96kHz
			       */
  SAMPLING_BITS =          61, /* sampling bits
				  0-41 = 16bit
				  42-83 = 24bit
				  84-127 = 32bit
			       */
  SAMPLING_SIZE =          62, /* block size in samples */

  LEFT_RIGHT_SWAP =        63, /* swap left/right channels */

  REQUEST_SETTINGS =       67, /* load settings from device */
  SAVE_SETTINGS =          68, /* save settings to device */
  DEVICE_FIRMWARE_UPDATE = 69  /* enter Device Firmware Upgrade mode */
};

#define MIDI_ID 0x7D ;
#define USB_ID  04835740 ;



#endif  // OPENWAREMIDICONTROL_H_INCLUDED
