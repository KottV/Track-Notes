/*
  ==============================================================================

    TimestampWidget.cpp
    Created: 1 Mar 2020 12:03:54am
    Author:  Joseph Lyons

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimestampWidget.h"
#include "TimestampContainerWidget.h"

//==============================================================================
TimestampWidget::TimestampWidget (const double& timeInSeconds)
    : timecode (timeInSeconds)
//      shouldDeleteTimestamp (false)
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

TimestampWidget::~TimestampWidget()
{
    timestampLabelPtr = nullptr;
    timestampNotesPtr = nullptr;
    removeTimestampButtonPtr = nullptr;
}

bool TimestampWidget::operator< (const TimestampWidget& timestampWidgetRight)
{
    return timecode < timestampWidgetRight.timecode;
}

void TimestampWidget::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (Colours::grey);
}

void TimestampWidget::resized()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::row;

    const float FLEX_VALUE = 2.5;
    
    fb.items
        .add (FlexItem (*timestampLabelPtr)
        .withFlex (FLEX_VALUE)
        .withMaxHeight (getHeight())
        .withMaxWidth (getWidth() * (3.0 / 16.0)));
    fb.items
        .add (FlexItem (*timestampNotesPtr)
        .withFlex (FLEX_VALUE)
        .withMaxHeight (getHeight()));
    fb.items
        .add (FlexItem (*removeTimestampButtonPtr)
        .withFlex (FLEX_VALUE)
        .withMaxHeight (getHeight()).withMaxWidth (getWidth() / 8));

    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    fb.performLayout (getLocalBounds().toFloat());
}

void TimestampWidget::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == removeTimestampButtonPtr.get())
    {
        shouldDeleteTimestamp = true;
        findParentComponentOfClass<TimestampContainerWidget>()->flexBoxRelayout();
//        delete this;
    }
}

bool TimestampWidget::getShouldDeleteTimestamp()
{
    return shouldDeleteTimestamp;
}
