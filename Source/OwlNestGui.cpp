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

#include "OwlNestGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OwlNestGui::OwlNestGui (OwlNestSettings& settings, AudioDeviceManager& dm, Value& updateGui)
    : Component ("MainGui"),
      theSettings(settings), theDm(dm)
{
    addAndMakeVisible (samplingRateComboBox = new ComboBox ("new combo box"));
    samplingRateComboBox->setEditableText (false);
    samplingRateComboBox->setJustificationType (Justification::centredLeft);
    samplingRateComboBox->setTextWhenNothingSelected (String::empty);
    samplingRateComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    samplingRateComboBox->addItem ("8 kHz", 1);
    samplingRateComboBox->addItem ("32 kHz", 2);
    samplingRateComboBox->addItem ("48 kHz", 3);
    samplingRateComboBox->addItem ("96 kHz", 4);
    samplingRateComboBox->addListener (this);

    addAndMakeVisible (samplingRateLabel = new Label ("new label",
                                                      "Sampling Rate"));
    samplingRateLabel->setFont (Font (15.00f, Font::plain));
    samplingRateLabel->setJustificationType (Justification::centredLeft);
    samplingRateLabel->setEditable (false, false, false);
    samplingRateLabel->setColour (TextEditor::textColourId, Colours::black);
    samplingRateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (loadButton = new TextButton ("new button"));
    loadButton->setButtonText ("load from owl");
    loadButton->addListener (this);

    addAndMakeVisible (leftGainSlider = new Slider ("new slider"));
    leftGainSlider->setRange (0, 127, 1);
    leftGainSlider->setSliderStyle (Slider::LinearHorizontal);
    leftGainSlider->setTextBoxStyle (Slider::TextBoxRight, true, 35, 20);
    leftGainSlider->addListener (this);

    addAndMakeVisible (leftGainLabel = new Label ("new label",
                                                  "Input Gain L"));
    leftGainLabel->setFont (Font (15.00f, Font::plain));
    leftGainLabel->setJustificationType (Justification::centredLeft);
    leftGainLabel->setEditable (false, false, false);
    leftGainLabel->setColour (TextEditor::textColourId, Colours::black);
    leftGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saveButton = new TextButton ("new button"));
    saveButton->setButtonText ("save to owl");
    saveButton->addListener (this);

    addAndMakeVisible (dfuButton = new TextButton ("new button"));
    dfuButton->setButtonText ("Firmware Update");
    dfuButton->addListener (this);

    addAndMakeVisible (bypassButton = new ToggleButton ("new toggle button"));
    bypassButton->setButtonText ("Bypass");
    bypassButton->addListener (this);

    addAndMakeVisible (swapLRButton = new ToggleButton ("new toggle button"));
    swapLRButton->setButtonText ("Swap Left/Right");
    swapLRButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 700);


    //[Constructor] You can add your own custom stuff here..
    addAndMakeVisible (audioSelector = new AudioDeviceSelectorComponent(theDm,0,0,0,0,true,true,false,true));
    audioSelector->setBounds(8,8,300,200);
    settingsChanged();
    updateGui.addListener(this);
    setVisible(true); // set the window visible
    //[/Constructor]
}

OwlNestGui::~OwlNestGui()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    samplingRateComboBox = nullptr;
    samplingRateLabel = nullptr;
    loadButton = nullptr;
    leftGainSlider = nullptr;
    leftGainLabel = nullptr;
    saveButton = nullptr;
    dfuButton = nullptr;
    bypassButton = nullptr;
    swapLRButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    audioSelector = nullptr;
    //[/Destructor]
}

//==============================================================================
void OwlNestGui::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OwlNestGui::resized()
{
    samplingRateComboBox->setBounds (129, 368, 150, 24);
    samplingRateLabel->setBounds (24, 368, 103, 24);
    loadButton->setBounds (24, 336, 150, 24);
    leftGainSlider->setBounds (128, 416, 150, 24);
    leftGainLabel->setBounds (24, 416, 103, 24);
    saveButton->setBounds (224, 336, 150, 24);
    dfuButton->setBounds (128, 456, 150, 24);
    bypassButton->setBounds (24, 240, 150, 24);
    swapLRButton->setBounds (24, 280, 150, 24);
    //[UserResized] Add your own custom resize handling here..
//    audioSelector->setBounds(8,8,300,200);
    //[/UserResized]
}

void OwlNestGui::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    int cc=-1;
    int val = 0;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == samplingRateComboBox)
    {
        //[UserComboBoxCode_samplingRateComboBox] -- add your combo box handling code here..
        cc=SAMPLING_RATE;
        switch (samplingRateComboBox->getSelectedId()) {
            case 1: // 8kHz
                val = 0;
                break;
            case 2: // 32kHz
                val = 32;
                break;
            case 3: // 48kHz
                val = 64;
                break;
            case 4: // 96kHz
                val = 96;
                break;
            default:
                val = 64;
                break;
        }
        //[/UserComboBoxCode_samplingRateComboBox]
    }

    //[UsercomboBoxChanged_Post]
    theSettings.setCc(cc, val);
    //[/UsercomboBoxChanged_Post]
}

void OwlNestGui::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        theSettings.LoadFromOwl();
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        theSettings.SaveToOwl();
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == dfuButton)
    {
        //[UserButtonCode_dfuButton] -- add your button handler code here..
        theSettings.setCc(DEVICE_FIRMWARE_UPDATE, 127);
        //[/UserButtonCode_dfuButton]
    }
    else if (buttonThatWasClicked == bypassButton)
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
      theSettings.setCc(BYPASS, bypassButton->getToggleState() ? 127 : 0);	
        //[/UserButtonCode_bypassButton]
    }
    else if (buttonThatWasClicked == swapLRButton)
    {
        //[UserButtonCode_swapLRButton] -- add your button handler code here..
      theSettings.setCc(LEFT_RIGHT_SWAP, swapLRButton->getToggleState() ? 127 : 0);	
        //[/UserButtonCode_swapLRButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void OwlNestGui::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    int cc=-1;
    int val = 0;
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == leftGainSlider)
    {
        //[UserSliderCode_leftGainSlider] -- add your slider handling code here..
        val=leftGainSlider->getValue();
	cc = LEFT_INPUT_GAIN;
        //[/UserSliderCode_leftGainSlider]
    }

    //[UsersliderValueChanged_Post]
    theSettings.setCc(cc, val);
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OwlNestGui::valueChanged(juce::Value &value){
    settingsChanged();
}

void OwlNestGui::settingsChanged() {
    int v;

    // Sampling rate
    v = theSettings.getCc(SAMPLING_RATE)>>5;
    samplingRateComboBox->setSelectedId(v+1, dontSendNotification);

    if(theSettings.getCc(BYPASS) == 127)
      bypassButton->setToggleState(true, dontSendNotification);
    else
      bypassButton->setToggleState(false, dontSendNotification);

    if(theSettings.getCc(LEFT_RIGHT_SWAP) == 127)
      swapLRButton->setToggleState(true, dontSendNotification);
    else
      swapLRButton->setToggleState(false, dontSendNotification);

    // Left Input Gain
    leftGainSlider->setValue(theSettings.getCc(LEFT_INPUT_GAIN), dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OwlNestGui" componentName="MainGui"
                 parentClasses="public Component, public Value::Listener" constructorParams="OwlNestSettings&amp; settings, AudioDeviceManager&amp; dm, Value&amp; updateGui"
                 variableInitialisers="theSettings(settings), theDm(dm)&#10;&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="700">
  <BACKGROUND backgroundColour="ffffffff"/>
  <COMBOBOX name="new combo box" id="7eed9fbfa06bf85b" memberName="samplingRateComboBox"
            virtualName="" explicitFocusOrder="0" pos="129 368 150 24" editable="0"
            layout="33" items="8 kHz&#10;32 kHz&#10;48 kHz&#10;96 kHz" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="aedcbbc865265e" memberName="samplingRateLabel"
         virtualName="" explicitFocusOrder="0" pos="24 368 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sampling Rate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="712a98a25b0d275e" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="24 336 150 24" buttonText="load from owl"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="new slider" id="ce099269a95e9cf7" memberName="leftGainSlider"
          virtualName="" explicitFocusOrder="0" pos="128 416 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="0" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2138fad0eb10f8ee" memberName="leftGainLabel"
         virtualName="" explicitFocusOrder="0" pos="24 416 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain L" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="f37a6fa0e6074e35" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="224 336 150 24" buttonText="save to owl"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="49395e88504ed9a4" memberName="dfuButton"
              virtualName="" explicitFocusOrder="0" pos="128 456 150 24" buttonText="Firmware Update"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="2c9068f31b4a945b" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="24 240 150 24" buttonText="Bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="5e0a14ed17680a7" memberName="swapLRButton"
                virtualName="" explicitFocusOrder="0" pos="24 280 150 24" buttonText="Swap Left/Right"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
