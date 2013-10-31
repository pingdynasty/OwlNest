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
#include "Enums.h"

class SeriesDeviceCallBacks : public AudioIODeviceCallback, public Value::Listener
{
    
private:
    AudioProcessorPlayer processorA;
    AudioProcessorPlayer processorB;
    AudioSourcePlayer player;
    ScopedPointer<AudioFormatReaderSource> source;
    StompBoxAudioProcessor stompboxA;
    StompBoxAudioProcessor stompboxB;
    bool audioModeState = false;
    
    
   ConfigModes configuration = SINGLE;
    Value& patchState;
    Value& owlConfig;
    Value& stompAPatch;
    Value& stompBPatch;
    Value& transportValue;

    float** buffer;
    int channels, samples;
public:
    
    SeriesDeviceCallBacks(Value& patchChange,Value& owlConfig,Value& stompAPatch, Value& stompBPatch,Value& transportValue);
    ~SeriesDeviceCallBacks();
    
    virtual void 	audioDeviceIOCallback (const float **inputChannelData, int numInputChannels, float **outputChannelData, int numOutputChannels, int numSamples);
    
    virtual void 	audioDeviceAboutToStart (AudioIODevice *device);
    
    virtual void 	audioDeviceStopped ();
    
    void valueChanged(juce::Value &patchChange);
    
    StompBoxAudioProcessor& getStompboxA();
    StompBoxAudioProcessor& getStompboxB();
    
    void setInputFile(File input);
    
    void play();
    
    void stop();
    
    void  pause();
    
    void fileMode();
    
    void removeBuffer();
   
    
    
    void audioInMode();
    
    
    
    
    
// void processorPlayerCallBack();
};



#endif  // SERIESDEVICECALLBACKS_H_INCLUDED
