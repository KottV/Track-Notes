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
    notesPtr->setMultiLine (true);
    notesPtr->setReturnKeyStartsNewLine (true);
    notesPtr->setReadOnly (false);
    notesPtr->setScrollbarsShown (true);
    notesPtr->setCaretVisible (true);
    notesPtr->setPopupMenuEnabled (true);
    notesPtr->setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    notesPtr->setColour (TextEditor::highlightColourId, Colours::black);
    notesPtr->setColour (TextEditor::outlineColourId, Colour (Colours::white));
    notesPtr->setText (notes);

    removeTimestampButtonPtr.reset (new TextButton ("Remove"));
//    removeTimestampButtonPtr->setLookAndFeel (staticTextSizeButtonPtr.get());
    removeTimestampButtonPtr->addListener (this);
    addAndMakeVisible (removeTimestampButtonPtr.get());
    removeTimestampButtonPtr->setColour (TextButton::buttonColourId, Colour (0xff393939));
    removeTimestampButtonPtr->setColour (TextButton::textColourOnId, Colours::white);
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

TimestampData Timestamp::getTimestampData() const
{
    TimestampData timestampData;

    timestampData.timeInSeconds = timecode.getTimecodeInSeconds();
    timestampData.timecodeString = timecode.getTimecodeString();
    timestampData.notes = notesPtr->getText();

    return timestampData;
}

void Timestamp::setNotes (const String& notesString)
{
    notesPtr->setText (notesString);
}
