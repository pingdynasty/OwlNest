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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ApplicationSettingsWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ApplicationSettingsWindow::ApplicationSettingsWindow (AudioDeviceManager& deviceManager)
{
    addAndMakeVisible (audioSelector = new AudioDeviceSelectorComponent (deviceManager,0,2,0,2,true,true,false,false));
    audioSelector->setName ("new component");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
//   addAndMakeVisible (audioSelector = new AudioDeviceSelectorComponent(deviceManager,0,0,0,0,true,true,false,true));
//    audioSelector->setBounds(8,8,300,200);
    setVisible(true);
    //[/Constructor]
}

ApplicationSettingsWindow::~ApplicationSettingsWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioSelector = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ApplicationSettingsWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffbdbdbd));

    g.setColour (Colour (0xff2aa54f));
    g.fillRect (44, 100, 100, 100);

    g.setColour (Colour (0xff2aa567));
    g.fillPath (internalPath1);

    g.setColour (Colour (0xff2aa55e));
    g.fillRoundedRectangle (516.0f, 124.0f, 100.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff2aa570));
    g.fillRoundedRectangle (132.0f, 356.0f, 100.0f, 100.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ApplicationSettingsWindow::resized()
{
    audioSelector->setBounds (0, 0, 392, 528);
    internalPath1.clear();
    internalPath1.startNewSubPath (406.0f, 360.0f);
    internalPath1.lineTo (436.0f, 410.0f);
    internalPath1.lineTo (376.0f, 410.0f);
    internalPath1.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ApplicationSettingsWindow"
                 componentName="" parentClasses="public Component" constructorParams="AudioDeviceManager&amp; deviceManager"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffbdbdbd">
    <RECT pos="44 100 100 100" fill="solid: ff2aa54f" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: ff2aa567" hasStroke="0" nonZeroWinding="1">s 406 360 l 436 410 l 376 410 x</PATH>
    <ROUNDRECT pos="516 124 100 100" cornerSize="10" fill="solid: ff2aa55e"
               hasStroke="0"/>
    <ROUNDRECT pos="132 356 100 100" cornerSize="10" fill="solid: ff2aa570"
               hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="new component" id="29b98dd09a98b370" memberName="audioSelector"
                    virtualName="" explicitFocusOrder="0" pos="0 0 392 528" class="AudioDeviceSelectorComponent"
                    params="deviceManager,0,0,0,0,true,true,false,true"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
