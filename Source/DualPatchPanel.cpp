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

#include "DualPatchPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DualPatchPanel::DualPatchPanel (StringArray patches, Value& patchChange,Value& owlConfig,Value& stompAPatch,                                 Value& stompBPatch)
    : patchState(patchChange), dualOwlConfig(owlConfig),dualStompAPatch(stompAPatch), dualStompBPatch(stompBPatch)
{
    addAndMakeVisible (configMode = new ComboBox ("new combo box"));
    configMode->setEditableText (false);
    configMode->setJustificationType (Justification::centredLeft);
    configMode->setTextWhenNothingSelected (String::empty);
    configMode->setTextWhenNoChoicesAvailable ("(no choices)");
    configMode->addListener (this);

    addAndMakeVisible (patchA = new ComboBox ("new combo box"));
    patchA->setEditableText (false);
    patchA->setJustificationType (Justification::centredLeft);
    patchA->setTextWhenNothingSelected (String::empty);
    patchA->setTextWhenNoChoicesAvailable ("(no choices)");
    patchA->addListener (this);

    addAndMakeVisible (patchB = new ComboBox ("new combo box"));
    patchB->setEditableText (false);
    patchB->setJustificationType (Justification::centredLeft);
    patchB->setTextWhenNothingSelected (String::empty);
    patchB->setTextWhenNoChoicesAvailable ("(no choices)");
    patchB->addListener (this);

    addAndMakeVisible (buttonA = new TextButton ("new button"));
    buttonA->setButtonText ("A");
    buttonA->addListener (this);
    buttonA->setColour (TextButton::buttonColourId, Colour (0xffd50000));
    buttonA->setColour (TextButton::buttonOnColourId, Colour (0xff0cbc00));

    addAndMakeVisible (buttonB = new TextButton ("new button"));
    buttonB->setButtonText ("B");
    buttonB->addListener (this);
    buttonB->setColour (TextButton::buttonColourId, Colour (0xffd50000));
    buttonB->setColour (TextButton::buttonOnColourId, Colour (0xff0cbc00));


    //[UserPreSize]

    //[/UserPreSize]

    setSize (252, 185);


    //[Constructor] You can add your own custom stuff here..

    setTopLeftPosition(529, 0);

    patchA->addItemList(patches, 1);
    patchA->setTextWhenNothingSelected(stompAPatch.getValue());
    patchA->setText(stompAPatch.getValue());

    patchB->addItemList( patches, 1);
    patchB->setTextWhenNothingSelected(stompBPatch.getValue());
    patchB->setText(stompBPatch.getValue());


    StringArray modes;

    modes.addTokens("Single Dual Series Parallel", false);


    configMode->addItemList(modes, 1);
    configMode->setTextWhenNothingSelected(modes[0]);
    configMode->setText(modes[owlConfig.getValue()]);
   patchState.addListener(this);

    //[/Constructor]
}

DualPatchPanel::~DualPatchPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    configMode = nullptr;
    patchA = nullptr;
    patchB = nullptr;
    buttonA = nullptr;
    buttonB = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DualPatchPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DualPatchPanel::resized()
{
    configMode->setBounds (16, 16, 150, 24);
    patchA->setBounds (16, 96, 150, 24);
    patchB->setBounds (16, 144, 150, 24);
    buttonA->setBounds (176, 96, 24, 24);
    buttonB->setBounds (176, 144, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DualPatchPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == configMode)
    {
        //[UserComboBoxCode_configMode] -- add your combo box handling code here..


        dualOwlConfig.setValue(configMode->getSelectedItemIndex());



        //[/UserComboBoxCode_configMode]
    }
    else if (comboBoxThatHasChanged == patchA)
    {
        //[UserComboBoxCode_patchA] -- add your combo box handling code here..

        String js=patchA->getText(); // JUCE string
        dualStompAPatch.setValue(js);




        //[/UserComboBoxCode_patchA]
    }
    else if (comboBoxThatHasChanged == patchB)
    {
        //[UserComboBoxCode_patchB] -- add your combo box handling code here..

        String js=patchB->getText(); // JUCE string
        dualStompBPatch.setValue(js);


        //[/UserComboBoxCode_patchB]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void DualPatchPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == buttonA)
    {
        //[UserButtonCode_buttonA] -- add your button handler code here..
        //[/UserButtonCode_buttonA]
    }
    else if (buttonThatWasClicked == buttonB)
    {
        //[UserButtonCode_buttonB] -- add your button handler code here..
        //[/UserButtonCode_buttonB]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void DualPatchPanel::valueChanged(juce::Value& valueChange)
{

   if(valueChange == patchState)
   {

        switch((int) patchState.getValue())
        {
            case A:
            {
                buttonB->setColour(TextButton::buttonColourId, Colours::red);
                buttonA->setColour(TextButton::buttonColourId,Colours::green);
                break;
            }

            case B:
            {
                buttonA->setColour(TextButton::buttonColourId,Colours::red);
                buttonB->setColour(TextButton::buttonColourId, Colours::green);
                break;
            }

        }

   }




}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DualPatchPanel" componentName=""
                 parentClasses="public Component, public Value::Listener" constructorParams="StringArray patches, Value&amp; patchChange,Value&amp; owlConfig,Value&amp; stompAPatch,                                 Value&amp; stompBPatch"
                 variableInitialisers="patchState(patchChange), dualOwlConfig(owlConfig),dualStompAPatch(stompAPatch), dualStompBPatch(stompBPatch)&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="252" initialHeight="185">
  <BACKGROUND backgroundColour="ffffffff"/>
  <COMBOBOX name="new combo box" id="be5da53c5ac94829" memberName="configMode"
            virtualName="" explicitFocusOrder="0" pos="16 16 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="18d82cbc522ab47f" memberName="patchA"
            virtualName="" explicitFocusOrder="0" pos="16 96 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="8c5f11dabd968937" memberName="patchB"
            virtualName="" explicitFocusOrder="0" pos="16 144 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="45770c82e0f94c9e" memberName="buttonA"
              virtualName="" explicitFocusOrder="0" pos="176 96 24 24" bgColOff="ffd50000"
              bgColOn="ff0cbc00" buttonText="A" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="c871a619e7eea525" memberName="buttonB"
              virtualName="" explicitFocusOrder="0" pos="176 144 24 24" bgColOff="ffd50000"
              bgColOn="ff0cbc00" buttonText="B" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
