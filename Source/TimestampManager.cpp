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
    : HEIGHT_OF_TIMESTAMP_WIDGETS (height / 6), WIDTH (width)
{
}

TimestampManager::~TimestampManager()
{
}

void TimestampManager::paint (Graphics& g)
{
    g.drawRect (getLocalBounds(), 1);
    g.setColour (Colours::white);
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

Array<std::pair<double, String>> TimestampManager::getData() const
{
    Array<std::pair<double, String>> data;

    for (auto& i : timestampOwnedArray)
        data.add (std::pair<double, String>(i->getTimecodeInSeconds(), i->getNotes()));

    return data;
}
