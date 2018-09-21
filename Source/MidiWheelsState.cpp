/*
  ==============================================================================

    MidiWheelsState.cpp
    Created: 21 Sep 2018 4:04:28pm
    Author:  Peter

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiWheelsState.h"

//==============================================================================
MidiWheelsState::MidiWheelsState()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MidiWheelsState::~MidiWheelsState()
{
}

//==============================================================================
void MidiWheelsState::reset()
{
    const ScopedLock sl (lock);
    zerostruct (wheelStates);
    eventsToAdd.clear();
}

void MidiWheelsState::processNextMidiEvent (const MidiMessage& message)
{
    if (message.isPitchWheel())
    {
        pitchWheelInternal (message.getChannel(), message.getPitchWheelValue());
    }
    else if (message.isNoteOff())
    {
        modWheelInternal (message.getChannel(), message.getControllerValue());
    }
}
void MidiWheelsState::processNextMidiBuffer (MidiBuffer& buffer,
                                               const int startSample,
                                               const int numSamples,
                                               const bool injectIndirectEvents)
{
    MidiBuffer::Iterator i (buffer);
    MidiMessage message;
    int time;

    const ScopedLock sl (lock);

    while (i.getNextEvent (message, time))
        processNextMidiEvent (message);

    if (injectIndirectEvents)
    {
        MidiBuffer::Iterator i2 (eventsToAdd);
        const int firstEventToAdd = eventsToAdd.getFirstEventTime();
        const double scaleFactor = numSamples / (double) (eventsToAdd.getLastEventTime() + 1 - firstEventToAdd);

        while (i2.getNextEvent (message, time))
        {
            const int pos = jlimit (0, numSamples - 1, roundToInt ((time - firstEventToAdd) * scaleFactor));
            buffer.addEvent (message, startSample + pos);
        }
    }

    eventsToAdd.clear();
}
//==============================================================================


void MidiWheelsState::pitchWheelInternal (int midiChannel,  int position)
{
    for (int i = listeners.size(); --i >= 0;)
            listeners.getUnchecked(i)->handlePitchWheel (this, midiChannel, position);
}
void MidiWheelsState::modWheelInternal (int midiChannel,  int position)
{
    for (int i = listeners.size(); --i >= 0;)
            listeners.getUnchecked(i)->handleModWheel (this, midiChannel, position);
}

//==============================================================================
void MidiWheelsState::addListener (MidiWheelsStateListener* const listener)
{
    const ScopedLock sl (lock);
    listeners.addIfNotAlreadyThere (listener);
}

void MidiWheelsState::removeListener (MidiWheelsStateListener* const listener)
{
    const ScopedLock sl (lock);
    listeners.removeFirstMatchingValue (listener);
}
//==============================================================================

