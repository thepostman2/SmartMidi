/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MidiWheelsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MidiWheelsComponent::MidiWheelsComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    PitchWheel.reset (new Slider ("PitchWheel"));
    addAndMakeVisible (PitchWheel.get());
    PitchWheel->setRange (-63, 63, 1);
    PitchWheel->setSliderStyle (Slider::LinearVertical);
    PitchWheel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    PitchWheel->addListener (this);

    PitchWheel->setBounds (0, 0, 30, 100);

    ModWheel.reset (new Slider ("ModWheel"));
    addAndMakeVisible (ModWheel.get());
    ModWheel->setRange (0, 127, 0);
    ModWheel->setSliderStyle (Slider::LinearVertical);
    ModWheel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    ModWheel->addListener (this);

    ModWheel->setBounds (30, 0, 30, 100);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (60, 100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MidiWheelsComponent::~MidiWheelsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    PitchWheel = nullptr;
    ModWheel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MidiWheelsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MidiWheelsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MidiWheelsComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == PitchWheel.get())
    {
        //[UserSliderCode_PitchWheel] -- add your slider handling code here..

        //[/UserSliderCode_PitchWheel]
    }
    else if (sliderThatWasMoved == ModWheel.get())
    {
        //[UserSliderCode_ModWheel] -- add your slider handling code here..
        //[/UserSliderCode_ModWheel]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MidiWheelsComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="60" initialHeight="100">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="PitchWheel" id="4ac3051334472c90" memberName="PitchWheel"
          virtualName="" explicitFocusOrder="0" pos="0 0 30 100" min="-63.00000000000000000000"
          max="63.00000000000000000000" int="1.00000000000000000000" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="ModWheel" id="c13d971d7d7630f9" memberName="ModWheel" virtualName=""
          explicitFocusOrder="0" pos="30 0 30 100" min="0.00000000000000000000"
          max="127.00000000000000000000" int="0.00000000000000000000" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
