/*
  ==============================================================================

    TimestampManager.cpp
    Created: 1 Mar 2020 4:42:09pm
    Author:  Joseph Lyons

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimestampManager.h"

//==============================================================================
TimestampManager::TimestampManager (const unsigned int& width, const unsigned int& height)
    : HEIGHT_OF_TIMESTAMP_WIDGETS (height / 5), WIDTH (width)
{
}

TimestampManager::~TimestampManager()
{
}

void TimestampManager::paint (Graphics& g)
{
}

void TimestampManager::resized()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;

    const float FLEX_VALUE = 2.5;

    for (auto it = timestampOwnedArray.begin(); it != timestampOwnedArray.end(); it++)
    {
        fb.items
            .add (FlexItem (**it)
            .withFlex (FLEX_VALUE)
            .withMinHeight (HEIGHT_OF_TIMESTAMP_WIDGETS)
            .withMaxHeight (HEIGHT_OF_TIMESTAMP_WIDGETS)
            .withMaxWidth (WIDTH));
        addAndMakeVisible (**it);
    }

    layoutRectangle.setBounds(
        0,
        0,
        WIDTH,
        (unsigned int) (HEIGHT_OF_TIMESTAMP_WIDGETS) * timestampOwnedArray.size()
    );

    fb.performLayout (layoutRectangle);
    setSize (layoutRectangle.getWidth(), layoutRectangle.getHeight());
}

void TimestampManager::addTimestamp (const double& timeInSeconds, const String& notes)
{
    timestampOwnedArray.addSorted (timestampElementComparator, new Timestamp (timeInSeconds, notes));
    resized();
}

void TimestampManager::deleteChild (Timestamp* child)
{
    timestampOwnedArray.removeObject (child);
    resized();
}

Array<TimestampData> TimestampManager::getTimestampDataArray() const
{
    Array<TimestampData> timestampDataArray;

    for (auto& i : timestampOwnedArray)
    {
        TimestampData timestampData;

        timestampData.timeInSeconds = i->getTimestampData().timeInSeconds;
        timestampData.timecodeString = i->getTimestampData().timecodeString;
        timestampData.notes = i->getTimestampData().notes;

        timestampDataArray.add (timestampData);
    }

    return timestampDataArray;
}

int TimestampManager::getNumberOfTimestamps() const
{
    return timestampOwnedArray.size();
}

void TimestampManager::setNotes (unsigned int index, const String& notesString) const
{
    int last = timestampOwnedArray.size() - 1;

    if (index > last)
        index = last;

    timestampOwnedArray[index]->setNotes (notesString);
}
