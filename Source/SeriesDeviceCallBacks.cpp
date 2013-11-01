/*
  ==============================================================================

    SeriesDeviceCallBacks.cpp
    Created: 1 Oct 2013 4:23:29pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#include "SeriesDeviceCallBacks.h"

SeriesDeviceCallBacks:: SeriesDeviceCallBacks(Value& patchChange,Value& owlConfig,Value& stompAPatch, Value& stompBPatch, Value& transportValue)
:    source(NULL), buffer(NULL), patchState(patchChange),sdcbOwlConfig(owlConfig), sdcbStompAPatch(stompAPatch),sdcbStompBPatch(stompBPatch),sdcbTransportValue(transportValue)




{
    processorA.setProcessor(&stompboxA);
    processorB.setProcessor(&stompboxB);
    patchState.addListener(this);
    owlConfig.addListener(this);
    sdcbStompAPatch.addListener(this);
    sdcbStompBPatch.addListener(this);
    sdcbTransportValue.addListener(this);
    removeBuffer();
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
                switch((int) patchState.getValue())
                {
                case A:
                    {
                         processorA.audioDeviceIOCallback((const float**)processInput, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                        break;
                    }
                    case B:
                    {
                           processorB.audioDeviceIOCallback((const float**)processInput, numOutputChannels, outputChannelData, numOutputChannels, numSamples);
                        break;
                    }
                }
               
             
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
                if(numInputChannels >= 1)
                {
                    float** leftInput = &processInput[0];
                    float** rightInput = &processInput[1];
                    float** leftOutput = &outputChannelData[0];
                    float** rightOutput = &outputChannelData[1];
                    processorA.audioDeviceIOCallback((const float**)rightInput, 1, leftOutput, 1, numSamples);
                    processorB.audioDeviceIOCallback((const float**)leftInput, 1, rightOutput, 1, numSamples);
               } 
                break;
                
              
            }
        }

}

void SeriesDeviceCallBacks::setInputFile(File input){
    
    
    FileInputStream* stream = input.createInputStream();
    CoreAudioFormat format;

    source = new AudioFormatReaderSource(format.createReaderFor(stream, false), true);
  
    audioModeState = true;
 
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

 void SeriesDeviceCallBacks::valueChanged(juce::Value& valueChange)
{
    if(valueChange == patchState)
    {
    patchState.setValue(patchState.getValue());
    }
    else if (valueChange == sdcbOwlConfig)
    {
        configuration  = ConfigModes((int) sdcbOwlConfig.getValue());
    }
    else if (valueChange == sdcbStompAPatch)
    {
        String patch = sdcbStompAPatch.getValue();
        std::string ss (patch.toUTF8()); // convert to std::string
        stompboxA.setPatch(ss);
        processorA.setProcessor(&stompboxA);
    }
    else if (valueChange == sdcbStompBPatch)
    {
        String patch = sdcbStompBPatch.getValue();
        std::string ss (patch.toUTF8()); // convert to std::string
        stompboxB.setPatch(ss);
        processorB.setProcessor(&stompboxB);
    }
    else if (valueChange == sdcbTransportValue)
    {
        switch((int) sdcbTransportValue.getValue())
        {
            case PLAY:
            {
                if(player.getCurrentSource() != 0|| source != NULL)
                {
                    player.setSource(source);
                }
                break;
            }
                
            case PAUSE:
            {
                 player.setSource(NULL);
                break;
            }
            case STOP:
            {
                if(player.getCurrentSource() != 0|| source != NULL)
                {
                    player.setSource(NULL);
                    source->releaseResources();
                    source = NULL;
                }
                break;
            }
            case RECORD:
            {
                break;
            }
            case FILEMODE:
            {
                audioModeState = true;
                break;
            }
            case AUDIOIN:
            {
                if(player.getCurrentSource() != 0|| source != NULL)
                {
                    player.setSource(NULL);
                    source->releaseResources();
                    source = NULL;
                    
                }
                
                audioModeState = false;
                break;
            }
        }
    }
}


void SeriesDeviceCallBacks::audioDeviceAboutToStart (AudioIODevice *device)
{
    
    channels = device->getActiveOutputChannels().toInteger();
    samples = device->getCurrentBufferSizeSamples();
   
    removeBuffer();
    
    buffer = new float * [channels];
    for(int i=0; i<channels; ++i)
    {
        buffer[i] = new float[samples];
    }
    processorA.audioDeviceAboutToStart(device);
    processorB.audioDeviceAboutToStart(device);
    player.audioDeviceAboutToStart(device);
   
}

void SeriesDeviceCallBacks::removeBuffer()
{
     if(buffer != NULL){
        for(int i=0; i<channels; ++i)
            delete buffer[i];
        delete buffer;
    buffer = NULL;
     }
   
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
    removeBuffer();
}

/*
SeriesDeviceCallBacks :: SeriesDeviceCallBacks

: AudioIODeviceCallback


*/
