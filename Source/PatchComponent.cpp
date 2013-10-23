#include "PatchComponent.h"

PatchComponent::PatchComponent(AudioDeviceManager& dm) 
  : Component("Patch") {
  StompBoxAudioProcessor& stompbox = sdcb.getStompbox();
  editor = stompbox.createEditor();
  addAndMakeVisible(editor);
  dm.addAudioCallback(&sdcb);
}
