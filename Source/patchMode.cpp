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

#include "PatchMode.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
patchModeSwitching::patchModeSwitching (SeriesDeviceCallBacks& sdcb,juce::Value& patchState)
    : patchSdcb(sdcb), patchChange(patchState)
{
    addAndMakeVisible (patchModeButton = new TextButton (String::empty));
    patchModeButton->addListener (this);
    patchModeButton->setColour (TextButton::buttonColourId, Colour (0xffbababa));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (30, 30);


    //[Constructor] You can add your own custom stuff here..
    setTopLeftPosition(248, 176);
    //[/Constructor]
}

patchModeSwitching::~patchModeSwitching()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    patchModeButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void patchModeSwitching::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void patchModeSwitching::resized()
{
    patchModeButton->setBounds (3, 3, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void patchModeSwitching::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == patchModeButton)
    {
        //[UserButtonCode_patchModeButton] -- add your button handler code here..


        switch ((int) patchChange.getValue()) {
            case A:
            {
                patchChange.setValue(B);

                break;
            }
            case B:
            {
                patchChange.setValue(A);

                break;
            }

        }




        //[/UserButtonCode_patchModeButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="patchModeSwitching" componentName=""
                 parentClasses="public Component, public Value" constructorParams="SeriesDeviceCallBacks&amp; sdcb,juce::Value&amp; patchState"
                 variableInitialisers="patchSdcb(sdcb), patchChange(patchState)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="30" initialHeight="30">
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTBUTTON name="" id="c4aa3eaf9ceb752" memberName="patchModeButton" virtualName=""
              explicitFocusOrder="0" pos="3 3 24 24" bgColOff="ffbababa" buttonText=""
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
