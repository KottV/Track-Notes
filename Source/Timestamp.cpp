/*
  ==============================================================================

    Timestamp.cpp
    Created: 1 Mar 2020 12:03:54am
    Author:  Joseph Lyons

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Timestamp.h"
#include "TimestampManager.h"

//==============================================================================
Timestamp::Timestamp (const double& timeInSeconds)
    : timecode (timeInSeconds)
{
    timestampLabelPtr.reset (new Label ("timestampLabel", timecode.getTimecodeString()));
    timestampNotesPtr.reset (new TextEditor);
    removeTimestampButtonPtr.reset (new TextButton ("Remove"));

    removeTimestampButtonPtr->setLookAndFeel (staticTextSizeButtonPtr.get());
    removeTimestampButtonPtr->addListener (this);

    addAndMakeVisible (timestampLabelPtr.get());
    addAndMakeVisible (timestampNotesPtr.get());
    addAndMakeVisible (removeTimestampButtonPtr.get());
}

Timestamp::~Timestamp()
{
    timestampLabelPtr = nullptr;
    timestampNotesPtr = nullptr;
    removeTimestampButtonPtr = nullptr;
}

bool Timestamp::operator< (const Timestamp& TimestampRight) const
{
    return timecode < TimestampRight.timecode;
}

void Timestamp::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (Colours::grey);
}

void Timestamp::resized()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::row;

    const float FLEX_VALUE = 2.5;
    
    fb.items
        .add (FlexItem (*timestampLabelPtr)
        .withFlex (FLEX_VALUE)
        .withMaxHeight (getHeight())
        .withMaxWidth (getWidth() * (5.0 / 32.0)));
    fb.items
        .add (FlexItem (*timestampNotesPtr)
        .withFlex (FLEX_VALUE)
        .withMaxHeight (getHeight()));
    fb.items
        .add (FlexItem (*removeTimestampButtonPtr)
        .withFlex (FLEX_VALUE)
        .withMaxHeight (getHeight())
        .withMaxWidth (getWidth() / 8));

    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    fb.performLayout (getLocalBounds().toFloat());
}

void Timestamp::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == removeTimestampButtonPtr.get())
    {
        MessageManager::callAsync ([this]
        {
            findParentComponentOfClass<TimestampManager>()->deleteChild (this);
        });
    }
}
