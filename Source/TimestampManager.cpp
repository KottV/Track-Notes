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
TimestampManager::TimestampManager()
{
}

TimestampManager::~TimestampManager()
{
}

void TimestampManager::paint (Graphics& g)
{
//    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (Colours::white);
    g.setFont (14.0f);
}

void TimestampManager::resized()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;

    const float FLEX_VALUE = 2.5;
    const unsigned int NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW = 6;

    for (auto it = TimestampOwnedArray.begin(); it != TimestampOwnedArray.end(); it++)
    {
        fb.items
            .add (FlexItem (**it)
            .withFlex (FLEX_VALUE)
            .withMinHeight (getHeight() / NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW)
            .withMaxHeight (getHeight() / NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW)
            .withMaxWidth (getWidth()));
        addAndMakeVisible (**it);
    }

    Rectangle<int> layoutRectangle (
        0,
        0,
        getWidth(),
        (unsigned int) (getHeight() / NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW) * TimestampOwnedArray.size()
    );

    fb.performLayout (layoutRectangle);
}

void TimestampManager::addTimestamp (const double& timeInSeconds)
{
    TimestampOwnedArray.addSorted (timestampElementComparator, new Timestamp (timeInSeconds));
    resized();
}

void TimestampManager::deleteChild (Timestamp* child)
{
    TimestampOwnedArray.removeObject (child);
    resized();
}
