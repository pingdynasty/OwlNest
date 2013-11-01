/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_2C4D0C6A45459C02__
#define __JUCE_HEADER_2C4D0C6A45459C02__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SeriesDeviceCallBacks.h"
#include "Enums.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TransportPanel  : public Component,
                        public Value,
                        public ButtonListener
{
public:
    //==============================================================================
    TransportPanel ( SeriesDeviceCallBacks& sdcb, Value& transportValue);
    ~TransportPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    File getTestFile();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* arrowright_png;
    static const int arrowright_pngSize;
    static const char* image011_jpg;
    static const int image011_jpgSize;
    static const char* image012_jpg;
    static const int image012_jpgSize;
    static const char* image012_jpg2;
    static const int image012_jpg2Size;
    static const char* image013_jpg;
    static const int image013_jpgSize;
    static const char* image014_jpg;
    static const int image014_jpgSize;
    static const char* image011_jpg2;
    static const int image011_jpg2Size;
    static const char* image012_jpg3;
    static const int image012_jpg3Size;
    static const char* image013_jpg2;
    static const int image013_jpg2Size;
    static const char* image014_jpg2;
    static const int image014_jpg2Size;
    static const char* play_jpg;
    static const int play_jpgSize;
    static const char* pause_jpg;
    static const int pause_jpgSize;
    static const char* stop_jpg;
    static const int stop_jpgSize;
    static const char* record_jpg;
    static const int record_jpgSize;
    static const char* play_png;
    static const int play_pngSize;
    static const char* pause_png;
    static const int pause_pngSize;
    static const char* stop_png;
    static const int stop_pngSize;
    static const char* stop_png2;
    static const int stop_png2Size;
    static const char* record_png;
    static const int record_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
        SeriesDeviceCallBacks& transportSdcb;
        Value& transportPanelValue;
         File testAudioFile;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ImageButton> PlayButton;
    ScopedPointer<ImageButton> PauseButton;
    ScopedPointer<ImageButton> StopButton;
    ScopedPointer<ImageButton> RecordButton;
    ScopedPointer<TextEditor> filePath;
    ScopedPointer<TextButton> chooseFile;
    ScopedPointer<TextButton> audioInButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2C4D0C6A45459C02__
