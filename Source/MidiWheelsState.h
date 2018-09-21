/*
  ==============================================================================

    MidiWheelsState.h
    Created: 21 Sep 2018 4:04:28pm
    Author:  Peter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MidiWheelsState    : public Component
{
public:
    MidiWheelsState();
    ~MidiWheelsState();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiWheelsState)
};
