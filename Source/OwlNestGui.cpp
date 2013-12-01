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
#include "OwlNestGui.h"


//[/Headers]

#include "OwlNestGui.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OwlNestGui::OwlNestGui (OwlNestSettings& settings, AudioDeviceManager& dm, Value& updateGui)
    : theSettings(settings), theDm(dm)
{
    setName ("MainGui");
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
    loadButton->setButtonText ("Load from OWL");
    loadButton->addListener (this);

    addAndMakeVisible (leftGainSlider = new Slider ("new slider"));
    leftGainSlider->setRange (0, 127, 1);
    leftGainSlider->setSliderStyle (Slider::LinearHorizontal);
    leftGainSlider->setTextBoxStyle (Slider::TextBoxRight, false, 35, 20);
    leftGainSlider->addListener (this);

    addAndMakeVisible (leftGainLabel = new Label ("new label",
                                                  "Input Gain L"));
    leftGainLabel->setFont (Font (15.00f, Font::plain));
    leftGainLabel->setJustificationType (Justification::centredLeft);
    leftGainLabel->setEditable (false, false, false);
    leftGainLabel->setColour (TextEditor::textColourId, Colours::black);
    leftGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saveButton = new TextButton ("new button"));
    saveButton->setButtonText ("Save to OWL");
    saveButton->addListener (this);

    addAndMakeVisible (dfuButton = new TextButton ("new button"));
    dfuButton->setButtonText ("Firmware Update");
    dfuButton->addListener (this);

    addAndMakeVisible (bypassButton = new ToggleButton ("new toggle button"));
    bypassButton->setButtonText ("Codec Bypass");
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
    rightGainSlider->setTextBoxStyle (Slider::TextBoxRight, false, 35, 20);
    rightGainSlider->addListener (this);

    addAndMakeVisible (leftOutGainSlider = new Slider ("new slider"));
    leftOutGainSlider->setRange (0, 127, 1);
    leftOutGainSlider->setSliderStyle (Slider::LinearHorizontal);
    leftOutGainSlider->setTextBoxStyle (Slider::TextBoxRight, false, 35, 20);
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
    rightOutGainSlider->setTextBoxStyle (Slider::TextBoxRight, false, 35, 20);
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

    addAndMakeVisible (ledButton = new TextButton ("new button"));
    ledButton->setButtonText ("LED");
    ledButton->addListener (this);
    ledButton->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (protocolComboBox = new ComboBox ("new combo box"));
    protocolComboBox->setEditableText (false);
    protocolComboBox->setJustificationType (Justification::centredLeft);
    protocolComboBox->setTextWhenNothingSelected (String::empty);
    protocolComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    protocolComboBox->addItem ("Philips", 1);
    protocolComboBox->addItem ("MSB", 2);
    protocolComboBox->addListener (this);

    addAndMakeVisible (protocolLabel = new Label ("new label",
                                                  "Protocol"));
    protocolLabel->setFont (Font (15.00f, Font::plain));
    protocolLabel->setJustificationType (Justification::centredLeft);
    protocolLabel->setEditable (false, false, false);
    protocolLabel->setColour (TextEditor::textColourId, Colours::black);
    protocolLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (masterButton = new ToggleButton ("new toggle button"));
    masterButton->setButtonText ("Master");
    masterButton->addListener (this);

    addAndMakeVisible (statusLabel = new Label ("new label",
                                                "Status: Initialising..."));
    statusLabel->setFont (Font (15.00f, Font::plain));
    statusLabel->setJustificationType (Justification::centredLeft);
    statusLabel->setEditable (false, false, false);
    statusLabel->setColour (TextEditor::textColourId, Colours::black);
    statusLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (patchSlotAComboBox = new ComboBox ("new combo box"));
    patchSlotAComboBox->setEditableText (false);
    patchSlotAComboBox->setJustificationType (Justification::centredLeft);
    patchSlotAComboBox->setTextWhenNothingSelected (String::empty);
    patchSlotAComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    patchSlotAComboBox->addItem ("...", 1);
    patchSlotAComboBox->addListener (this);

    addAndMakeVisible (patchSlotALabel = new Label ("new label",
                                                    "Green Slot"));
    patchSlotALabel->setFont (Font (15.00f, Font::plain));
    patchSlotALabel->setJustificationType (Justification::centredRight);
    patchSlotALabel->setEditable (false, false, false);
    patchSlotALabel->setColour (TextEditor::textColourId, Colours::black);
    patchSlotALabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (patchSlotBComboBox = new ComboBox ("new combo box"));
    patchSlotBComboBox->setEditableText (false);
    patchSlotBComboBox->setJustificationType (Justification::centredLeft);
    patchSlotBComboBox->setTextWhenNothingSelected (String::empty);
    patchSlotBComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    patchSlotBComboBox->addItem ("...", 1);
    patchSlotBComboBox->addListener (this);

    addAndMakeVisible (patchSlotBLabel = new Label ("new label",
                                                    "Red Slot"));
    patchSlotBLabel->setFont (Font (15.00f, Font::plain));
    patchSlotBLabel->setJustificationType (Justification::centredRight);
    patchSlotBLabel->setEditable (false, false, false);
    patchSlotBLabel->setColour (TextEditor::textColourId, Colours::black);
    patchSlotBLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (resetButton = new TextButton ("new button"));
    resetButton->setButtonText ("Factory Reset");
    resetButton->addListener (this);

    addAndMakeVisible (patchSlotBComboBox2 = new ComboBox ("new combo box"));
    patchSlotBComboBox2->setEditableText (false);
    patchSlotBComboBox2->setJustificationType (Justification::centredLeft);
    patchSlotBComboBox2->setTextWhenNothingSelected (String::empty);
    patchSlotBComboBox2->setTextWhenNoChoicesAvailable ("(no choices)");
    patchSlotBComboBox2->addItem ("High", 1);
    patchSlotBComboBox2->addItem ("Low", 2);
    patchSlotBComboBox2->addListener (this);

    addAndMakeVisible (patchSlotBLabel2 = new Label ("new label",
                                                     "Sensitivity"));
    patchSlotBLabel2->setFont (Font (15.00f, Font::plain));
    patchSlotBLabel2->setJustificationType (Justification::centredRight);
    patchSlotBLabel2->setEditable (false, false, false);
    patchSlotBLabel2->setColour (TextEditor::textColourId, Colours::black);
    patchSlotBLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (ConnexionButton = new TextButton ("new button"));
    ConnexionButton->setButtonText (String::empty);
    ConnexionButton->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (connexionStatusLabel = new Label ("new label",
                                                         "Connexion Status"));
    connexionStatusLabel->setFont (Font (15.00f, Font::plain));
    connexionStatusLabel->setJustificationType (Justification::centredRight);
    connexionStatusLabel->setEditable (false, false, false);
    connexionStatusLabel->setColour (TextEditor::textColourId, Colours::black);
    connexionStatusLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (779, 700);


    //[Constructor] You can add your own custom stuff here..

    settingsChanged();
    updateGui.addListener(this);
    setVisible(true); // set the window visible
    setStatus("ready");
    timerInterval=2000;
    startTimer(timerInterval);

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
    ledButton = nullptr;
    protocolComboBox = nullptr;
    protocolLabel = nullptr;
    masterButton = nullptr;
    statusLabel = nullptr;
    patchSlotAComboBox = nullptr;
    patchSlotALabel = nullptr;
    patchSlotBComboBox = nullptr;
    patchSlotBLabel = nullptr;
    resetButton = nullptr;
    patchSlotBComboBox2 = nullptr;
    patchSlotBLabel2 = nullptr;
    ConnexionButton = nullptr;
    connexionStatusLabel = nullptr;


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
    samplingRateComboBox->setBounds (521, 520, 150, 24);
    samplingRateLabel->setBounds (416, 520, 103, 24);
    loadButton->setBounds (184, 104, 150, 24);
    leftGainSlider->setBounds (120, 492, 150, 24);
    leftGainLabel->setBounds (16, 492, 103, 24);
    saveButton->setBounds (416, 104, 150, 24);
    dfuButton->setBounds (456, 16, 150, 24);
    bypassButton->setBounds (424, 488, 150, 24);
    swapLRButton->setBounds (608, 488, 150, 24);
    rightGainLabel->setBounds (16, 521, 103, 24);
    rightGainSlider->setBounds (120, 521, 150, 24);
    leftOutGainSlider->setBounds (120, 556, 150, 24);
    leftOutGainLabel->setBounds (16, 556, 103, 24);
    rightOutGainLabel->setBounds (16, 585, 103, 24);
    rightOutGainSlider->setBounds (120, 585, 150, 24);
    leftInputMuteButton->setBounds (280, 492, 100, 24);
    rightInputMuteButton->setBounds (280, 521, 100, 24);
    leftOutputMuteButton->setBounds (280, 556, 100, 24);
    rightOutputMuteButton->setBounds (280, 585, 100, 24);
    samplingBitsComboBox->setBounds (521, 552, 150, 24);
    samplingBitsLabel->setBounds (416, 552, 103, 24);
    ledButton->setBounds (344, 208, 64, 64);
    protocolComboBox->setBounds (521, 584, 150, 24);
    protocolLabel->setBounds (416, 584, 103, 24);
    masterButton->setBounds (680, 584, 96, 24);
    statusLabel->setBounds (184, 128, 352, 24);
    patchSlotAComboBox->setBounds (120, 216, 150, 24);
    patchSlotALabel->setBounds (48, 216, 72, 24);
    patchSlotBComboBox->setBounds (120, 248, 150, 24);
    patchSlotBLabel->setBounds (48, 248, 72, 24);
    resetButton->setBounds (616, 16, 150, 24);
    patchSlotBComboBox2->setBounds (552, 216, 150, 24);
    patchSlotBLabel2->setBounds (464, 216, 88, 24);
    ConnexionButton->setBounds (19, 17, 16, 16);
    connexionStatusLabel->setBounds (39, 13, 96, 24);
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
    else if (comboBoxThatHasChanged == protocolComboBox)
    {
        //[UserComboBoxCode_protocolComboBox] -- add your combo box handling code here..
      cc = CODEC_PROTOCOL;
      val = protocolComboBox->getSelectedId() == 1 ? 0 : 127;
        //[/UserComboBoxCode_protocolComboBox]
    }
    else if (comboBoxThatHasChanged == patchSlotAComboBox)
    {
        //[UserComboBoxCode_patchSlotAComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_patchSlotAComboBox]
    }
    else if (comboBoxThatHasChanged == patchSlotBComboBox)
    {
        //[UserComboBoxCode_patchSlotBComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_patchSlotBComboBox]
    }
    else if (comboBoxThatHasChanged == patchSlotBComboBox2)
    {
        //[UserComboBoxCode_patchSlotBComboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_patchSlotBComboBox2]
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
	setStatus("Loading settings...");
        theSettings.loadFromOwl();
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        theSettings.saveToOwl();
	setStatus("Saved settings to OWL");
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == dfuButton)
    {
        //[UserButtonCode_dfuButton] -- add your button handler code here..
      setStatus("Updating firmware");
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
        theSettings.setCc(LEFT_OUTPUT_MUTE, leftOutputMuteButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_leftOutputMuteButton]
    }
    else if (buttonThatWasClicked == rightOutputMuteButton)
    {
        //[UserButtonCode_rightOutputMuteButton] -- add your button handler code here..
        theSettings.setCc(RIGHT_OUTPUT_MUTE, rightOutputMuteButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_rightOutputMuteButton]
    }
    else if (buttonThatWasClicked == ledButton)
    {
        //[UserButtonCode_ledButton] -- add your button handler code here..
      theSettings.setCc(PATCH_BUTTON, 127);
      theSettings.setCc(REQUEST_SETTINGS, 30); // to get the updated LED value
        //[/UserButtonCode_ledButton]
    }
    else if (buttonThatWasClicked == masterButton)
    {
        //[UserButtonCode_masterButton] -- add your button handler code here..
      theSettings.setCc(CODEC_MASTER, masterButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_masterButton]
    }
    else if (buttonThatWasClicked == resetButton)
    {
        //[UserButtonCode_resetButton] -- add your button handler code here..
      theSettings.setCc(FACTORY_RESET, resetButton->getToggleState() ? 127 : 0);
        //[/UserButtonCode_resetButton]
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

void OwlNestGui::setStatus(const juce::String& msg){
  statusLabel->setText(msg, dontSendNotification);
}

void OwlNestGui::settingsChanged() {
    StringArray& names = theSettings.getPresetNames();
    patchSlotAComboBox->clear(dontSendNotification);
    patchSlotBComboBox->clear(dontSendNotification);
    patchSlotAComboBox->addItemList(names, 1);
    patchSlotBComboBox->addItemList(names, 1);

    // LED button
    int v = theSettings.getCc(LED);
    Colour colour;
    if(v < 42){
      colour = Colour::fromRGB(0xbb, 0xbb, 0xff);
    }else if(v > 83){
      colour = Colour::fromRGB(0xff, 0, 0); // red
    }else{
      colour = Colour::fromRGB(0, 0xff, 0); // green
    }
    ledButton->setColour(TextButton::buttonColourId, colour);

    // Patches
    v = theSettings.getCc(PATCH_SLOT_GREEN);
    patchSlotAComboBox->setSelectedId(v+1, dontSendNotification);
    v = theSettings.getCc(PATCH_SLOT_RED);
    patchSlotBComboBox->setSelectedId(v+1, dontSendNotification);

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

    // Protocol
    if(theSettings.getCc(CODEC_PROTOCOL) < 64)
      protocolComboBox->setSelectedId(1);
    else
      protocolComboBox->setSelectedId(2);

    // Master
    if(theSettings.getCc(CODEC_MASTER) < 64)
      masterButton->setToggleState(false, dontSendNotification);
    else
      masterButton->setToggleState(true, dontSendNotification);
    setStatus("Loaded settings from OWL");
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
    setStatus("Updated OWL firmware");
  }else{
    setStatus("Firmware update cancelled");
  }
}

void OwlNestGui::timerCallback()
{
    if ((Time::getApproximateMillisecondCounter()-theSettings.getLastMidiMessageTime())>1.5*timerInterval)
    {
        ConnexionButton->setColour(TextButton::buttonColourId, Colour::fromRGB(0xff, 0, 0)); // red
    }
    else
    {
        ConnexionButton->setColour(TextButton::buttonColourId, Colour::fromRGB(0, 0xff, 0)); // green
    }
    theSettings.setCc(REQUEST_SETTINGS,LED); // ask to send a Midi Message to check connection
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OwlNestGui" componentName="MainGui"
                 parentClasses="public Component, public Value::Listener, public Timer"
                 constructorParams="OwlNestSettings&amp; settings, AudioDeviceManager&amp; dm, Value&amp; updateGui"
                 variableInitialisers="theSettings(settings), theDm(dm)&#10;&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="779" initialHeight="700">
  <BACKGROUND backgroundColour="ffffffff"/>
  <COMBOBOX name="new combo box" id="7eed9fbfa06bf85b" memberName="samplingRateComboBox"
            virtualName="" explicitFocusOrder="0" pos="521 520 150 24" editable="0"
            layout="33" items="8 kHz&#10;32 kHz&#10;48 kHz&#10;96 kHz" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="aedcbbc865265e" memberName="samplingRateLabel"
         virtualName="" explicitFocusOrder="0" pos="416 520 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sampling Rate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="712a98a25b0d275e" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="184 104 150 24" buttonText="Load from OWL"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="new slider" id="ce099269a95e9cf7" memberName="leftGainSlider"
          virtualName="" explicitFocusOrder="0" pos="120 492 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2138fad0eb10f8ee" memberName="leftGainLabel"
         virtualName="" explicitFocusOrder="0" pos="16 492 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain L" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="f37a6fa0e6074e35" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="416 104 150 24" buttonText="Save to OWL"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="49395e88504ed9a4" memberName="dfuButton"
              virtualName="" explicitFocusOrder="0" pos="456 16 150 24" buttonText="Firmware Update"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="2c9068f31b4a945b" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="424 488 150 24" buttonText="Codec Bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="5e0a14ed17680a7" memberName="swapLRButton"
                virtualName="" explicitFocusOrder="0" pos="608 488 150 24" buttonText="Swap Left/Right"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="a4c7e40cc3b84fa1" memberName="rightGainLabel"
         virtualName="" explicitFocusOrder="0" pos="16 521 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="751638225df21da5" memberName="rightGainSlider"
          virtualName="" explicitFocusOrder="0" pos="120 521 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="59927295068e5acd" memberName="leftOutGainSlider"
          virtualName="" explicitFocusOrder="0" pos="120 556 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="d2acb69e045cd837" memberName="leftOutGainLabel"
         virtualName="" explicitFocusOrder="0" pos="16 556 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain L" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f61d9f9ae7e5f004" memberName="rightOutGainLabel"
         virtualName="" explicitFocusOrder="0" pos="16 585 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="e520e83dc8199cec" memberName="rightOutGainSlider"
          virtualName="" explicitFocusOrder="0" pos="120 585 150 24" min="0"
          max="127" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="new toggle button" id="c3d4453ea3e0bad0" memberName="leftInputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="280 492 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="9d0155fca059ad2b" memberName="rightInputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="280 521 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="e8b8a82e4cc96eab" memberName="leftOutputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="280 556 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="47ae93ef5d84135f" memberName="rightOutputMuteButton"
                virtualName="" explicitFocusOrder="0" pos="280 585 100 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="68afb9201dff30b0" memberName="samplingBitsComboBox"
            virtualName="" explicitFocusOrder="0" pos="521 552 150 24" editable="0"
            layout="33" items="16 bit&#10;24 bit&#10;32 bit" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f3258eff2173a09d" memberName="samplingBitsLabel"
         virtualName="" explicitFocusOrder="0" pos="416 552 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sampling Bits" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="936c69781f0cac49" memberName="ledButton"
              virtualName="" explicitFocusOrder="0" pos="344 208 64 64" bgColOff="ff808080"
              buttonText="LED" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="8e9735eeb5b5f6cd" memberName="protocolComboBox"
            virtualName="" explicitFocusOrder="0" pos="521 584 150 24" editable="0"
            layout="33" items="Philips&#10;MSB" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="6f96ad882d073112" memberName="protocolLabel"
         virtualName="" explicitFocusOrder="0" pos="416 584 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Protocol" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="7ae50b59d73384c8" memberName="masterButton"
                virtualName="" explicitFocusOrder="0" pos="680 584 96 24" buttonText="Master"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="2f07a4c0694077f7" memberName="statusLabel"
         virtualName="" explicitFocusOrder="0" pos="184 128 352 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Status: Initialising..." editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="8a0d565fbe220bde" memberName="patchSlotAComboBox"
            virtualName="" explicitFocusOrder="0" pos="120 216 150 24" editable="0"
            layout="33" items="..." textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="54afa4d08d09d664" memberName="patchSlotALabel"
         virtualName="" explicitFocusOrder="0" pos="48 216 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Green Slot" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <COMBOBOX name="new combo box" id="ead688c04fb4a49e" memberName="patchSlotBComboBox"
            virtualName="" explicitFocusOrder="0" pos="120 248 150 24" editable="0"
            layout="33" items="..." textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="a882f7d2f19281a4" memberName="patchSlotBLabel"
         virtualName="" explicitFocusOrder="0" pos="48 248 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Red Slot" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="new button" id="6c02712dbfb4bb60" memberName="resetButton"
              virtualName="" explicitFocusOrder="0" pos="616 16 150 24" buttonText="Factory Reset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="c9b0c725f2c0d34c" memberName="patchSlotBComboBox2"
            virtualName="" explicitFocusOrder="0" pos="552 216 150 24" editable="0"
            layout="33" items="High&#10;Low" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="529eec60a7cf0c8b" memberName="patchSlotBLabel2"
         virtualName="" explicitFocusOrder="0" pos="464 216 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sensitivity" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="new button" id="295a2bbf61be8607" memberName="ConnexionButton"
              virtualName="" explicitFocusOrder="0" pos="19 17 16 16" bgColOff="ff808080"
              buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <LABEL name="new label" id="7aa7ef82c462108" memberName="connexionStatusLabel"
         virtualName="" explicitFocusOrder="0" pos="39 13 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Connexion Status" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
