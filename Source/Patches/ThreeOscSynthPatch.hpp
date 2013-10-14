#ifndef __ThreOscSynthPatch_hpp__
#define __ThreeOscSynthPatch_hpp__

#include "StompBox.h"
#include "math.h"

class ThreeOscSynthPatch : public Patch {
public:
  ThreeOscSynthPatch(){
    registerParameter(PARAMETER_A, "Frequency");
    registerParameter(PARAMETER_B, "Waveform");
    registerParameter(PARAMETER_C, "Amplitude");
      registerParameter(PARAMETER_D, "Phase");
      currentAngle =0.0;
      
  }
  void processAudio(AudioBuffer &buffer)
    {
    // put your code here!
        int numberofSamples = getBlockSize();
        float* buf = buffer.getSamples(0);
        float frequency = getParameterValue(PARAMETER_A)*5000; // frequency range defined here
        
        float waveTest = getParameterValue(PARAMETER_B);
        int wave = 0;
        float a = getParameterValue(PARAMETER_C) *2;
        if(getParameterValue(PARAMETER_D) < 0.5)
        {
            currentAngle = 0;
        }
            
        if(waveTest<=0.25)
        {
            wave = 0; //Saw
        }

        if(waveTest> 0.25 && waveTest<=0.5)
        {
            wave = 1; // Triangle
        }

        if(waveTest> 0.5 && waveTest<=0.75)
        {
            wave = 2; // Sine
        }

        if(waveTest > 0.75 && waveTest <= 1)
        {
            wave = 3; // Square
        }

   
        
        
    
        //Saw-----------------------------------------------------------
        
        float sawIncrement = 2*frequency/getSampleRate();
        
        if(wave == 0)
        {
            for(int K = 0; K < numberofSamples; K++)
            {
                currentAngle += sawIncrement;

                if(currentAngle > 1)
                {
                currentAngle-= 2;
                }
//                float val =currentAngle * a;
                buf[K]=currentAngle * a;
            }
        }
      
    //Triangle------------------------------------------------------
       
        float triIncrement = (sawIncrement * 2);
        ; //1 = up, -1 = down
        if(wave ==1)
        {
            for(int K = 0; K < numberofSamples;K++)
            {
               
                currentAngle+=triIncrement;

                if(currentAngle > 1)
                {
                  triIncrement *= -1; //down
                }
                if(currentAngle < -1)
                {
                  triIncrement  *= -1; // up
                }
               
                buf[K] = currentAngle * a;
            }
        }
        
    //Sine---------------------------------------------------------
        
        if(wave == 2)
        {
            for(int K = 0; K < numberofSamples; K++)
            {
                currentAngle += sawIncrement;
                
                if(currentAngle > 1)
                {
                    currentAngle -= 2;
                }
                
                
                buf[K]= (sin(currentAngle *  M_PI)) * a;
            }
        }
        
        
     //Square-------------------------------------------------------
        float squareValue = 0.99; // + and -
        if(wave ==3)
        {
            for(int K = 0; K < numberofSamples;K++)
            {
                currentAngle+=triIncrement;
                
                if(currentAngle > 1)
                {
                    squareValue = -0.99; //down
                    triIncrement *= -1;
                }
                if(currentAngle < -1)
                {
                    squareValue = 0.99; // up
                    triIncrement *= -1;
                }
                buf[K] = squareValue * a;
            }

        }
        
      
   }
private:
    float currentAngle; // state variable
};

#endif // __ThreeOscSynthPatch_hpp__
