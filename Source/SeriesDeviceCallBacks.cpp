/*
  ==============================================================================

    SeriesDeviceCallBacks.cpp
    Created: 1 Oct 2013 4:23:29pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#include "SeriesDeviceCallBacks.h"

SeriesDeviceCallBacks:: SeriesDeviceCallBacks()
:  source(NULL), buffer(NULL) {
    processorA.setProcessor(&stompboxA);
    processorB.setProcessor(&stompboxB);
}

SeriesDeviceCallBacks::~SeriesDeviceCallBacks(){
    
    if(buffer != NULL){
        for(int i=0; i<channels; ++i)
            delete buffer[i];
        delete buffer;
    }
    
    
}

StompBoxAudioProcessor& SeriesDeviceCallBacks::getStompboxA(){
   return stompboxA;
    
}
StompBoxAudioProcessor& SeriesDeviceCallBacks::getStompboxB(){
    return stompboxB;
    
}



void 	SeriesDeviceCallBacks::audioDeviceIOCallback (const float **inputChannelData, int numInputChannels, float **outputChannelData, int numOutputChannels, int numSamples)
{
    float **processInput;
    if(audioModeState) // audio file
    {
        jassert(channels >= numOutputChannels);
        jassert(samples == numSamples);
        
        player.audioDeviceIOCallback(inputChannelData, numInputChannels, buffer, numOutputChannels, numSamples);
        
        processInput = buffer;
    }
    else{
        processInput = ( float** )inputChannelData;
    }
    
        
        switch( configuration)
        {
            case SINGLE:
            {
          
            processorA.audioDeviceIOCallback((const float**)processInput, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                break;
            }
            case DUAL:
            {
                processorA.audioDeviceIOCallback((const float**)processInput, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                processorB.audioDeviceIOCallback((const float**)processInput, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                break;
            }
            case SERIES:
            {
                processorA.audioDeviceIOCallback((const float**)processInput, numOutputChannels, buffer, numOutputChannels, numSamples);
                processorB.audioDeviceIOCallback(( const float**)buffer, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                break;
            }
            case PARALLEL:
            {
                processorA.audioDeviceIOCallback((const float**)processInput, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                processorB.audioDeviceIOCallback((const float**)processInput, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                break;
            }
        }

}

void SeriesDeviceCallBacks::setInputFile(File input){
    
    
    FileInputStream* stream = input.createInputStream();
    CoreAudioFormat format;

    source = new AudioFormatReaderSource(format.createReaderFor(stream, false), true);
  
   
}

void SeriesDeviceCallBacks::audioInMode()
{
    stop();
    audioModeState = false;
}

void SeriesDeviceCallBacks::fileMode()
{
    audioModeState = true;
}

void SeriesDeviceCallBacks::stompAChange(std::string patch)
{
    stompboxA.setPatch(patch);
    processorA.setProcessor(&stompboxA);
}

void SeriesDeviceCallBacks::stompBChange(std::string patch)
{
    stompboxB.setPatch(patch);
    processorB.setProcessor(&stompboxB);
}



StringArray SeriesDeviceCallBacks:: getpatchesA()
{
    return  stompboxA.getPatchNames();
}

 String SeriesDeviceCallBacks::getCurrentPatchA()
{
    return stompboxA.getCurrentPatchName();
}

StringArray SeriesDeviceCallBacks:: getpatchesB()
{
    return  stompboxB.getPatchNames();
}

String SeriesDeviceCallBacks::getCurrentPatchB()
{
    return stompboxB.getCurrentPatchName();
}

void SeriesDeviceCallBacks::setConfiguration(int config)
{
    configuration  = configmodes(config);
    
	
}

void SeriesDeviceCallBacks::audioDeviceAboutToStart (AudioIODevice *device){
    
    channels = device->getActiveOutputChannels().toInteger();
    samples = device->getCurrentBufferSizeSamples();
    buffer = new float * [channels];
    for(int i=0; i<channels; ++i)
    {
        buffer[i] = new float[samples];
    }
    processorA.audioDeviceAboutToStart(device);
    processorB.audioDeviceAboutToStart(device);
    player.audioDeviceAboutToStart(device);
   
}



void SeriesDeviceCallBacks::play()
{
    if(player.getCurrentSource() != 0|| source != NULL)
    {
    player.setSource(source);
    }
}

void SeriesDeviceCallBacks::stop()
{
    if(player.getCurrentSource() != 0|| source != NULL)
    {
    player.setSource(NULL);
    source->releaseResources();
    source = NULL;
    }
}


void SeriesDeviceCallBacks::pause()
{
    player.setSource(NULL);
    
}


void 	SeriesDeviceCallBacks::audioDeviceStopped (){
    processorA.audioDeviceStopped();
    processorB.audioDeviceStopped();
    player.audioDeviceStopped();
    if(buffer != NULL){
        for(int i=0; i<channels; ++i)
            delete buffer[i];
        delete buffer;
    }
    buffer = NULL;
}

/*
SeriesDeviceCallBacks :: SeriesDeviceCallBacks

: AudioIODeviceCallback


*/
