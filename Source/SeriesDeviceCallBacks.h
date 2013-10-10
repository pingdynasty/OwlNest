/*
  ==============================================================================

    SeriesDeviceCallBacks.h
    Created: 1 Oct 2013 4:23:29pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#ifndef SERIESDEVICECALLBACKS_H_INCLUDED
#define SERIESDEVICECALLBACKS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Transport Panel.h"

class SeriesDeviceCallBacks : public AudioIODeviceCallback
{
    
private:
    AudioProcessorPlayer processor;
    AudioSourcePlayer player;
    ScopedPointer<AudioFormatReaderSource> source;
    StompBoxAudioProcessor stompbox;
    Transport

    float** buffer;
    int channels, samples;
public:
    
    SeriesDeviceCallBacks();
    ~SeriesDeviceCallBacks();
    
    virtual void 	audioDeviceIOCallback (const float **inputChannelData, int numInputChannels, float **outputChannelData, int numOutputChannels, int numSamples);
    
    virtual void 	audioDeviceAboutToStart (AudioIODevice *device);
    
    virtual void 	audioDeviceStopped ();

    StompBoxAudioProcessor& getStompbox();
    
    void setInputFile(File input);
//  void sourcePlayerCallBack();
    
// void processorPlayerCallBack();
};



#endif  // SERIESDEVICECALLBACKS_H_INCLUDED
