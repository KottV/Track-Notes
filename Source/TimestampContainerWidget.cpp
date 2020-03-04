/*
  ==============================================================================

    TimestampContainerWidget.cpp
    Created: 1 Mar 2020 4:42:09pm
    Author:  Joseph Lyons

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimestampContainerWidget.h"

//==============================================================================
TimestampContainerWidget::TimestampContainerWidget()
{
    viewportPtr->setBounds (0, 0, getWidth(), getHeight());
    viewportPtr.reset (new Viewport());
    addAndMakeVisible (viewportPtr.get());
}

TimestampContainerWidget::~TimestampContainerWidget()
{
}

void TimestampContainerWidget::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (Colours::white);
    g.setFont (14.0f);
}

void TimestampContainerWidget::resized()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;

    const float FLEX_VALUE = 2.5;
    const unsigned int NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW = 6;

    for (auto it = timestampWidgetOwnedArray.begin(); it != timestampWidgetOwnedArray.end(); it++)
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
        (unsigned int) (getHeight() / NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW) * timestampWidgetOwnedArray.size()
    );

    fb.performLayout (layoutRectangle);
}

void TimestampContainerWidget::addTimestampWidget (const double& timeInSeconds)
{
    timestampWidgetOwnedArray.addSorted (timestampElementComparator, new TimestampWidget (timeInSeconds));
    resized();
}

void TimestampContainerWidget::deleteChild (TimestampWidget* child)
{
    timestampWidgetOwnedArray.removeObject (child);
    resized();
}
