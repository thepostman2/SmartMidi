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
class MidiWheelsState;
//==============================================================================
/**
                                                                    //[Comments]
    auto-generated, created by the Projucer.

    This is a class similar to MidiKeyboardState. Instead of note on/offs
    wheel (pitch and mod)events are processed.
                                                                    //[/Comments]
*/
class MidiWheelsStateListener
{
public:
    //==============================================================================
    MidiWheelsStateListener() noexcept        {}
    virtual ~MidiWheelsStateListener()        {}
    
    //==============================================================================
    /** Called when one of the pitch Wheel is handled.
     
     This will be called synchronously when the state is either processing a
     buffer in its MidiWheelsState::processNextMidiBuffer() method, or
     when a wheel is being played with its MidiWheelsState::pitchWheel() method.
     
     Note that this callback could happen from an audio callback thread, so be
     careful not to block, and avoid any UI activity in the callback.
     */
    virtual void handlePitchWheel(MidiWheelsState* source,
                               int midiChannel, int position) = 0;
    
    /** Called when one of the MidiWheelState's mod wheel is handled.
     
     This will be called synchronously when the state is either processing a
     buffer in its MidiWheelsState::processNextMidiBuffer() method, or
     when a note is being played with its MidiWheelsState::modWheel() method.
     
     Note that this callback could happen from an audio callback thread, so be
     careful not to block, and avoid any UI activity in the callback.
     */
    virtual void handleModWheel (MidiWheelsState* source,
                                int midiChannel, int position) = 0;
};

class MidiWheelsState    
{
public:
    MidiWheelsState();
    ~MidiWheelsState();

    //==============================================================================
    /** Resets the state of the object.
     
     All internal data for all the channels is reset, but no events are sent as a
     result.
     
     If you want to release any keys that are currently down, and to send out note-up
     midi messages for this, use the allNotesOff() method instead.
     */
    void reset();

    //==============================================================================
    /** Looks at a wheel events and uses it to update the state of this object.
     
     To process a buffer full of midi messages, use the processNextMidiBuffer() method
     instead.
     */
    void processNextMidiEvent (const MidiMessage& message);
    
    /** Scans a midi stream for up/down events and adds its own events to it.
     
     This will look for any up/down events and use them to update the internal state,
     synchronously making suitable callbacks to the listeners.
     
     If injectIndirectEvents is true, then midi events to produce the recent noteOn()
     and noteOff() calls will be added into the buffer.
     
     Only the section of the buffer whose timestamps are between startSample and
     (startSample + numSamples) will be affected, and any events added will be placed
     between these times.
     
     If you're going to use this method, you'll need to keep calling it regularly for
     it to work satisfactorily.
     
     To process a single midi event at a time, use the processNextMidiEvent() method
     instead.
     */
    void processNextMidiBuffer (MidiBuffer& buffer,
                                int startSample,
                                int numSamples,
                                bool injectIndirectEvents);
    
    //==============================================================================
    /** Registers a listener for callbacks when keys go up or down.
     @see removeListener
     */
    void addListener (MidiWheelsStateListener* listener);
    
    /** Deregisters a listener.
     @see addListener
     */
    void removeListener (MidiWheelsStateListener* listener);
    
private:
    CriticalSection lock;
    uint16 wheelStates [2];
    MidiBuffer eventsToAdd;
    Array <MidiWheelsStateListener*> listeners;
    
    void pitchWheelInternal (int midiChannel,  int position);
    void modWheelInternal (int midiChannel,  int position);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiWheelsState)
};
