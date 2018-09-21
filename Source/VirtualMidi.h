/*
  ==============================================================================

    VirtualMidi.h
    Created: 21 Jul 2018 10:08:58am
    Author:  Peter

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class VirtualMidi    : public Component, public MidiInputCallback
{
public:
    VirtualMidi()

    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        vMidiInput=MidiInput::createNewDevice(MidiName, this);
        if( vMidiInput == nullptr ) {
            std::cout << "couldn't create virtual midi IN port for SmartMidi.\n";
        } else {
            vMidiInput->start();
        }
        vMidiOutput=MidiOutput::createNewDevice(MidiName);
    }

    ~VirtualMidi()
    {
        if(vMidiInput)
            vMidiInput->~MidiInput();
        if(vMidiOutput)
            vMidiOutput->~MidiOutput();
    }
    
    void handleIncomingMidiMessage (MidiInput *source, const MidiMessage &message)override
    {
        if(vMidiOutput)
            vMidiOutput->sendMessageNow(message);
    }
    
    void handlePartialSysexMessage (MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp)override
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("VirtualMidi", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
    void SendMessageNow(const juce::MidiMessage &message)
    {
        vMidiOutput->sendMessageNow(message);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualMidi)
    const String MidiName="SmartMidi";
    MidiInput* vMidiInput;
    MidiOutput* vMidiOutput;

};
