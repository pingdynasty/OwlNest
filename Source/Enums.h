/*
  ==============================================================================

    Enums.h
    Created: 24 Oct 2013 3:53:42pm
    Author:  Christofero Pollano

  ==============================================================================
*/

#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum  ConfigModes { SINGLE = 0,DUAL = 1,SERIES = 2,PARALLEL = 3};

enum PatchModes { A = 0, B = 1};

enum transportModes { PLAY= 1, PAUSE = 2, STOP = 3, RECORD = 4, AUDIOIN = 5, PREPAREFILEMODE = 6, FILEMODE = 7, STOPRECORDING = 8};

enum SensitivitySettings { LOW =1, MEDIUM, HIGH, CUSTOM};


#endif  // ENUMS_H_INCLUDED
