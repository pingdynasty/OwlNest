/*
  ==============================================================================

    factoryPatchesView.h
    Created: 27 Jun 2015 6:18:54pm
    Author:  Guillaume Le Nost

  ==============================================================================
*/

#ifndef FACTORYPATCHESVIEW_H_INCLUDED
#define FACTORYPATCHESVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class factoryPatchesView    : public Component
{
public:
    factoryPatchesView();
    ~factoryPatchesView();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (factoryPatchesView)
};


#endif  // FACTORYPATCHESVIEW_H_INCLUDED
