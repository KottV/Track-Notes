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
Timestamp::Timestamp (const double& timeInSeconds, const String& notes)
    : timecode (timeInSeconds)
{
    timecodeLabelPtr.reset (new Label ("timestampLabel", timecode.getTimecodeString()));
    addAndMakeVisible (timecodeLabelPtr.get());

    notesPtr.reset (new TextEditor);
    addAndMakeVisible (notesPtr.get());
    notesPtr->setText (notes);

    removeTimestampButtonPtr.reset (new TextButton ("Remove"));
    removeTimestampButtonPtr->setLookAndFeel (staticTextSizeButtonPtr.get());
    removeTimestampButtonPtr->addListener (this);
    addAndMakeVisible (removeTimestampButtonPtr.get());
}

Timestamp::~Timestamp()
{
    timecodeLabelPtr = nullptr;
    notesPtr = nullptr;
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
        .add (FlexItem (*timecodeLabelPtr)
        .withFlex (FLEX_VALUE)
        .withMaxHeight (getHeight())
        .withMaxWidth (getWidth() * (5.0 / 32.0)));
    fb.items
        .add (FlexItem (*notesPtr)
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

double Timestamp::getTimecodeInSeconds() const
{
    return timecode.getTimecodeInSeconds();
}

String Timestamp::getNotes() const
{
    return notesPtr->getText();
}
