/*
  ==============================================================================

    userPatchesView.h
    Created: 27 Jun 2015 6:19:33pm
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#ifndef USERPATCHESVIEW_H_INCLUDED
#define USERPATCHESVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class userPatchesView    : public Component
{
public:
    userPatchesView();
    ~userPatchesView();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (userPatchesView)
};


#endif  // USERPATCHESVIEW_H_INCLUDED
