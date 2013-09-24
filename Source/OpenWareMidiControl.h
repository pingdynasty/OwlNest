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
 
 cc     value		function
 
 32     0-127		left channel input gain, -34.5dB to +12dB (92 = 0dB)
 33     0-127		right channel input gain
 34     0-127		left channel output gain, -73dB to +6dB (121 = 0dB)
 35     0-127		right channel output gain
 36     127=mute	left channel mute
 37     127=mute	right channel mute
 38 	0-127		Codec Bypass mode
 60     0-127		sampling rate
        0-31 = 8kHz
        32-63 = 32kHz
        64-95 = 48kHz
        96-127 = 96kHz
 61     0-127		bit width
        0-41 = 16bit
        42-83 = 24bit
        84-127 = 32bit
 62     0-127		buffer size
 63     0-127		Swap left/right channels
        0-63 normal mode
        64-127 swapped mode
 67     127=request	load settings from device
 68     127=save	save settings to device
 69     127=DFU	enter Device Firmware Upgrade mode
 */

enum OpenWareMidiControl {
    LEFT_INPUT_GAIN =   32,
    RIGHT_INPUT_GAIN =  33,
    LEFT_OUTPUT_GAIN =  34,
    RIGHT_OUTPUT_GAIN = 35,
    LEFT_MUTE = 36,
    RIGHT_MUTE = 37,
    SAMPLING_RATE = 60,
    
    REQUEST_SETTINGS = 67,
    SAVE_SETTINGS = 68,
    DEVICE_FIRMWARE_UPDATE = 69
};

#define MIDI_ID 0x7D ;
#define USB_ID  04835740 ;



#endif  // OPENWAREMIDICONTROL_H_INCLUDED
