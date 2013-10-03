#ifndef __HighPassFilterPatch_hpp__
#define __HighPassFilterPatch_hpp__

#include "StompBox.h"

class HighPassFilterPatch : public Patch {
public:
  HighPassFilterPatch(){
    registerParameter(PARAMETER_A, "Fc");
  }
  void processAudio(AudioBuffer &buffer){
    // put your code here!
  }
};

#endif // __HighPassFilterPatch_hpp__
