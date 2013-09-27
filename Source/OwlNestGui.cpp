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
#include "FirmwareLoader.h"
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

    addAndMakeVisible (rightGainLabel = new Label ("new label",
                                                   "Input Gain R"));
    rightGainLabel->setFont (Font (15.00f, Font::plain));
    rightGainLabel->setJustificationType (Justification::centredLeft);
    rightGainLabel->setEditable (false, false, false);
    rightGainLabel->setColour (TextEditor::textColourId, Colours::black);
    rightGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rightGainSlider = new Slider ("new slider"));
    rightGainSlider->setRange (0, 127, 1);
    rightGainSlider->setSliderStyle (Slider::LinearHorizontal);
    rightGainSlider->setTextBoxStyle (Slider::TextBoxRight, true, 35, 20);
    rightGainSlider->addListener (this);

    addAndMakeVisible (leftOutGainSlider = new Slider ("new slider"));
    leftOutGainSlider->setRange (0, 127, 1);
    leftOutGainSlider->setSliderStyle (Slider::LinearHorizontal);
    leftOutGainSlider->setTextBoxStyle (Slider::TextBoxRight, true, 35, 20);
    leftOutGainSlider->addListener (this);

    addAndMakeVisible (leftOutGainLabel = new Label ("new label",
                                                     "Output Gain L"));
    leftOutGainLabel->setFont (Font (15.00f, Font::plain));
    leftOutGainLabel->setJustificationType (Justification::centredLeft);
    leftOutGainLabel->setEditable (false, false, false);
    leftOutGainLabel->setColour (TextEditor::textColourId, Colours::black);
    leftOutGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rightOutGainLabel = new Label ("new label",
                                                      "Output Gain R"));
    rightOutGainLabel->setFont (Font (15.00f, Font::plain));
    rightOutGainLabel->setJustificationType (Justification::centredLeft);
    rightOutGainLabel->setEditable (false, false, false);
    rightOutGainLabel->setColour (TextEditor::textColourId, Colours::black);
    rightOutGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rightOutGainSlider = new Slider ("new slider"));
    rightOutGainSlider->setRange (0, 127, 1);
    rightOutGainSlider->setSliderStyle (Slider::LinearHorizontal);
    rightOutGainSlider->setTextBoxStyle (Slider::TextBoxRight, true, 35, 20);
    rightOutGainSlider->addListener (this);

    addAndMakeVisible (leftInputMuteButton = new ToggleButton ("new toggle button"));
    leftInputMuteButton->setButtonText ("Mute");
    leftInputMuteButton->addListener (this);

    addAndMakeVisible (rightInputMuteButton = new ToggleButton ("new toggle button"));
    rightInputMuteButton->setButtonText ("Mute");
    rightInputMuteButton->addListener (this);

    addAndMakeVisible (leftOutputMuteButton = new ToggleButton ("new toggle button"));
    leftOutputMuteButton->setButtonText ("Mute");
    leftOutputMuteButton->addListener (this);

    addAndMakeVisible (rightOutputMuteButton = new ToggleButton ("new toggle button"));
    rightOutputMuteButton->setButtonText ("Mute");
    rightOutputMuteButton->addListener (this);

    addAndMakeVisible (samplingBitsComboBox = new ComboBox ("new combo box"));
    samplingBitsComboBox->setEditableText (false);
    samplingBitsComboBox->setJustificationType (Justification::centredLeft);
    samplingBitsComboBox->setTextWhenNothingSelected (String::empty);
    samplingBitsComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    samplingBitsComboBox->addItem ("16 bit", 1);
    samplingBitsComboBox->addItem ("24 bit", 2);
    samplingBitsComboBox->addItem ("32 bit", 3);
    samplingBitsComboBox->addListener (this);

    addAndMakeVisible (samplingBitsLabel = new Label ("new label",
                                                      "Sampling Bits"));
    samplingBitsLabel->setFont (Font (15.00f, Font::plain));
    samplingBitsLabel->setJustificationType (Justification::centredLeft);
    samplingBitsLabel->setEditable (false, false, false);
    samplingBitsLabel->setColour (TextEditor::textColourId, Colours::black);
    samplingBitsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


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
    rightGainLabel = nullptr;
    rightGainSlider = nullptr;
    leftOutGainSlider = nullptr;
    leftOutGainLabel = nullptr;
    rightOutGainLabel = nullptr;
    rightOutGainSlider = nullptr;
    leftInputMuteButton = nullptr;
    rightInputMuteButton = nullptr;
    leftOutputMuteButton = nullptr;
    rightOutputMuteButton = nullptr;
    samplingBitsComboBox = nullptr;
    samplingBitsLabel = nullptr;


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
    leftGainSlider->setBounds (128, 470, 150, 24);
    leftGainLabel->setBounds (24, 470, 103, 24);
    saveButton->setBounds (224, 336, 150, 24);
    dfuButton->setBounds (224, 248, 150, 24);
    bypassButton->setBounds (24, 240, 150, 24);
    swapLRButton->setBounds (24, 280, 150, 24);
    rightGainLabel->setBounds (24, 499, 103, 24);
    rightGainSlider->setBounds (128, 499, 150, 24);
    leftOutGainSlider->setBounds (128, 534, 150, 24);
    leftOutGainLabel->setBounds (24, 534, 103, 24);
    rightOutGainLabel->setBounds (24, 563, 103, 24);
    rightOutGainSlider->setBounds (128, 563, 150, 24);
    leftInputMuteButton->setBounds (288, 470, 100, 24);
    rightInputMuteButton->setBounds (288, 499, 100, 24);
    leftOutputMuteButton->setBounds (288, 534, 100, 24);
    rightOutputMuteButton->setBounds (288, 563, 100, 24);
    samplingBitsComboBox->setBounds (129, 400, 150, 24);
    samplingBitsLabel->setBounds (24, 400, 103, 24);
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
    else if (comboBoxThatHasChanged == samplingBitsComboBox)
    {
        //[UserComboBoxCode_samplingBitsComboBox] -- add your combo box handling code here..
        cc=SAMPLING_BITS;
        switch (samplingBitsComboBox->getSelectedId()) {
            case 1: // 16bit
                val = 0;
                break;
            case 2: // 24bit
                val = 42;
                break;
            case 3: // 32bit
                val = 84;
                break;
            default:
                val = 0;
                break;
        }
        //[/UserComboBoxCode_samplingBitsComboBox]
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
      updateFirmware();
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
    else if (buttonThatWasClicked == leftInputMuteButton)
    {
        //[UserButtonCode_leftInputMuteButton] -- add your button handler code here..
        theSettings.setCc(LEFT_INPUT_MUTE, leftInputMuteButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_leftInputMuteButton]
    }
    else if (buttonThatWasClicked == rightInputMuteButton)
    {
        //[UserButtonCode_rightInputMuteButton] -- add your button handler code here..
        theSettings.setCc(RIGHT_INPUT_MUTE, rightInputMuteButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_rightInputMuteButton]
    }
    else if (buttonThatWasClicked == leftOutputMuteButton)
    {
        //[UserButtonCode_leftOutputMuteButton] -- add your button handler code here..
        theSettings.setCc(LEFT_INPUT_MUTE, leftOutputMuteButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_leftOutputMuteButton]
    }
    else if (buttonThatWasClicked == rightOutputMuteButton)
    {
        //[UserButtonCode_rightOutputMuteButton] -- add your button handler code here..
        theSettings.setCc(RIGHT_OUTPUT_MUTE, rightOutputMuteButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_rightOutputMuteButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void OwlNestGui::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == leftGainSlider)
    {
        //[UserSliderCode_leftGainSlider] -- add your slider handling code here..
        theSettings.setCc(LEFT_INPUT_GAIN, leftGainSlider->getValue());
        //[/UserSliderCode_leftGainSlider]
    }
    else if (sliderThatWasMoved == rightGainSlider)
    {
        //[UserSliderCode_rightGainSlider] -- add your slider handling code here..
        theSettings.setCc(RIGHT_INPUT_GAIN, rightGainSlider->getValue());
        //[/UserSliderCode_rightGainSlider]
    }
    else if (sliderThatWasMoved == leftOutGainSlider)
    {
        //[UserSliderCode_leftOutGainSlider] -- add your slider handling code here..
        theSettings.setCc(LEFT_OUTPUT_GAIN,leftOutGainSlider->getValue());
        //[/UserSliderCode_leftOutGainSlider]
    }
    else if (sliderThatWasMoved == rightOutGainSlider)
    {
        //[UserSliderCode_rightOutGainSlider] -- add your slider handling code here..
        theSettings.setCc(RIGHT_OUTPUT_GAIN,rightOutGainSlider->getValue());
        //[/UserSliderCode_rightOutGainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OwlNestGui::valueChanged(juce::Value &value){
    settingsChanged();
}

void OwlNestGui::settingsChanged() {
    int v;

    // Sampling rate and bits
    v = theSettings.getCc(SAMPLING_RATE)>>5;
    samplingRateComboBox->setSelectedId(v+1, dontSendNotification);
    v = (int) theSettings.getCc(SAMPLING_BITS)/42;
    samplingBitsComboBox->setSelectedId(v+1, dontSendNotification);

    // Bypass
    if(theSettings.getCc(BYPASS) == 127)
      bypassButton->setToggleState(true, dontSendNotification);
    else
      bypassButton->setToggleState(false, dontSendNotification);

    // LR SWAP
    if(theSettings.getCc(LEFT_RIGHT_SWAP) == 127)
      swapLRButton->setToggleState(true, dontSendNotification);
    else
      swapLRButton->setToggleState(false, dontSendNotification);

    // Input/output Gains
    leftGainSlider->setValue(theSettings.getCc(LEFT_INPUT_GAIN), dontSendNotification);
    rightGainSlider->setValue(theSettings.getCc(RIGHT_INPUT_GAIN),dontSendNotification);
    leftOutGainSlider->setValue(theSettings.getCc(LEFT_OUTPUT_GAIN), dontSendNotification);
    rightOutGainSlider->setValue(theSettings.getCc(RIGHT_OUTPUT_GAIN), dontSendNotification);
    
    // Mute
    if(theSettings.getCc(LEFT_INPUT_MUTE) == 127)
        leftInputMuteButton->setToggleState(true, dontSendNotification);
    else
        leftInputMuteButton->setToggleState(false, dontSendNotification);
    if(theSettings.getCc(RIGHT_INPUT_MUTE) == 127)
        rightInputMuteButton->setToggleState(true, dontSendNotification);
    else
        rightInputMuteButton->setToggleState(false, dontSendNotification);
    if(theSettings.getCc(LEFT_OUTPUT_MUTE) == 127)
        leftOutputMuteButton->setToggleState(true, dontSendNotification);
    else
        leftOutputMuteButton->setToggleState(false, dontSendNotification);
    if(theSettings.getCc(RIGHT_OUTPUT_MUTE) == 127)
        rightOutputMuteButton->setToggleState(true, dontSendNotification);
    else
        rightOutputMuteButton->setToggleState(false, dontSendNotification);
}

void OwlNestGui::updateFirmware(){
  FileChooser chooser("Select Firmware", 
		      File::getSpecialLocation (File::currentApplicationFile),
// 		      File::getSpecialLocation (File::userHomeDirectory/),
		      "*.bin");
  if(chooser.browseForFileToOpen()){
    // put device into DFU mode
    theSettings.setCc(DEVICE_FIRMWARE_UPDATE, 127);
    File file = chooser.getResult();
    FirmwareLoader loader;
    loader.updateFirmware(file);
  }
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
          virtualName="" explicitFocusOrder="0" pos="128 470 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="0" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2138fad0eb10f8ee" memberName="leftGainLabel"
         virtualName="" explicitFocusOrder="0" pos="24 470 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain L" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="f37a6fa0e6074e35" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="224 336 150 24" buttonText="save to owl"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="49395e88504ed9a4" memberName="dfuButton"
              virtualName="" explicitFocusOrder="0" pos="224 248 150 24" buttonText="Firmware Update"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="2c9068f31b4a945b" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="24 240 150 24" buttonText="Bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="5e0a14ed17680a7" memberName="swapLRButton"
                virtualName="" explicitFocusOrder="0" pos="24 280 150 24" buttonText="Swap Left/Right"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="a4c7e40cc3b84fa1" memberName="rightGainLabel"
         virtualName="" explicitFocusOrder="0" pos="24 499 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="751638225df21da5" memberName="rightGainSlider"
          virtualName="" explicitFocusOrder="0" pos="128 499 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="0" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="59927295068e5acd" memberName="leftOutGainSlider"
          virtualName="" explicitFocusOrder="0" pos="128 534 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="0" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="d2acb69e045cd837" memberName="leftOutGainLabel"
         virtualName="" explicitFocusOrder="0" pos="24 534 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain L" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f61d9f9ae7e5f004" memberName="rightOutGainLabel"
         virtualName="" explicitFocusOrder="0" pos="24 563 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="e520e83dc8199cec" memberName="rightOutGainSlider"
          virtualName="" explicitFocusOrder="0" pos="128 563 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="0" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="new toggle button" id="c3d4453ea3e0bad0" memberName="leftInputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="288 470 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="9d0155fca059ad2b" memberName="rightInputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="288 499 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="e8b8a82e4cc96eab" memberName="leftOutputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="288 534 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="47ae93ef5d84135f" memberName="rightOutputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="288 563 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="68afb9201dff30b0" memberName="samplingBitsComboBox"
            virtualName="" explicitFocusOrder="0" pos="129 400 150 24" editable="0"
            layout="33" items="16 bit&#10;24 bit&#10;32 bit" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f3258eff2173a09d" memberName="samplingBitsLabel"
         virtualName="" explicitFocusOrder="0" pos="24 400 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sampling Bits" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
