/*
  ==============================================================================

    SeriesDeviceCallBacks.cpp
    Created: 1 Oct 2013 4:23:29pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#include "SeriesDeviceCallBacks.h"

SeriesDeviceCallBacks:: SeriesDeviceCallBacks()
: source(NULL), buffer(NULL) {
    processor.setProcessor(&stompbox);
}

SeriesDeviceCallBacks::~SeriesDeviceCallBacks(){
    if(buffer != NULL){
        for(int i=0; i<channels; ++i)
            delete buffer[i];
        delete buffer;
    }
}

StompBoxAudioProcessor& SeriesDeviceCallBacks::getStompbox(){
    return stompbox;
}

void 	SeriesDeviceCallBacks::audioDeviceIOCallback (const float **inputChannelData, int numInputChannels, float **outputChannelData, int numOutputChannels, int numSamples)
{
//     player.audioDeviceIOCallback(inputChannelData, numInputChannels,
//                                 buffer, channels, samples);
    
//     processor.audioDeviceIOCallback((const float**)buffer, channels, outputChannelData,
//                                     numOutputChannels, samples);

    processor.audioDeviceIOCallback(inputChannelData, numInputChannels, outputChannelData,
                                    numOutputChannels, samples);
    
}

void SeriesDeviceCallBacks::setInputFile(File input){
    FileInputStream* stream = input.createInputStream();
    CoreAudioFormat format;
    source = new AudioFormatReaderSource(format.createReaderFor(stream, false), true);
    player.setSource(source);
}


void SeriesDeviceCallBacks::audioDeviceAboutToStart (AudioIODevice *device){
    channels = device->getActiveOutputChannels().toInteger();
    samples = device->getCurrentBufferSizeSamples();
    buffer = new float * [channels];
    for(int i=0; i<channels; ++i)
        buffer[i] = new float[samples];
    processor.audioDeviceAboutToStart(device);
    player.audioDeviceAboutToStart(device);
}

void 	SeriesDeviceCallBacks::audioDeviceStopped (){
    processor.audioDeviceStopped();
    player.audioDeviceStopped();
}

/*
SeriesDeviceCallBacks :: SeriesDeviceCallBacks

: AudioIODeviceCallback


*/
