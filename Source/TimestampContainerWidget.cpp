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
    viewportPtr.reset (new Viewport);
    viewportPtr->setBounds (0, 0, getWidth(), getHeight());
    addAndMakeVisible (viewportPtr.get());
}

TimestampContainerWidget::TimestampContainerWidget (
    const std::vector<SafePointer<TimestampWidget>>& timestampWidgetPtrVector
)
    : timestampWidgetPtrVector (timestampWidgetPtrVector)
{
}

TimestampContainerWidget::~TimestampContainerWidget()
{
    cleanTimestampVector();

    for (auto& i : timestampWidgetPtrVector)
        delete i;
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
    
}

void TimestampContainerWidget::addTimestampWidget (const double& timeInSeconds)
{
    SafePointer<TimestampWidget> timestampWidgetPtr = new (std::nothrow) TimestampWidget (timeInSeconds);

    std::cout << timestampWidgetPtr << std::endl;

    timestampWidgetPtrVector.push_back (timestampWidgetPtr);
    cleanTimestampVector();
//    sortTimestampWidget();
    flexBoxRelayout();
}

void TimestampContainerWidget::cleanTimestampVector()
{
    for (auto it = timestampWidgetPtrVector.begin(); it != timestampWidgetPtrVector.end();)
    {
        if ((*it)->getShouldDeleteTimestamp())
        {
            delete *it;
            it = timestampWidgetPtrVector.erase (it);
        }
        else
            it++;
    }
}

void TimestampContainerWidget::flexBoxRelayout()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;

    const float FLEX_VALUE = 2.5;
    const unsigned int NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW = 6;
    unsigned int numberOfActiveTimestampWidgets = 0;

    for (auto it = timestampWidgetPtrVector.begin(); it != timestampWidgetPtrVector.end(); it++)
    {
        if (! (*it)->getShouldDeleteTimestamp())
        {
            numberOfActiveTimestampWidgets++;

            fb.items
                .add (FlexItem (**it)
                .withFlex (FLEX_VALUE)
                .withMinHeight (getHeight() / NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW)
                .withMaxHeight (getHeight() / NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW)
                .withMaxWidth (getWidth()));
            addAndMakeVisible (**it);
        }
        else
        {
            (*it)->setVisible (false);
            removeChildComponent (*it);
        }
    }

    Rectangle<int> rect (
        0,
        0,
        getWidth(),
        (unsigned int) (getHeight() / NUMBER_OF_TIMESTAMP_WIDGETS_IN_VIEW) * numberOfActiveTimestampWidgets
    );

    std::cout << timestampWidgetPtrVector.size() << std::endl;

    std::cout << rect.getHeight() << std::endl;

    fb.performLayout (rect);
}

void TimestampContainerWidget::sortTimestampWidget()
{
    std::sort (timestampWidgetPtrVector.begin(), timestampWidgetPtrVector.end());
}

//void TimestampContainerWidget::a (const TimestampWidget& a, const TimestampWidget& b)
//{
//    return a < b;
//}
