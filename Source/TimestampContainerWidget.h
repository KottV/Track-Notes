/*
  ==============================================================================

    TimestampContainerWidget.h
    Created: 1 Mar 2020 4:42:09pm
    Author:  Joseph Lyons

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TimestampWidget.h"

//==============================================================================
/*
*/
class TimestampContainerWidget    : public Component
{
public:
    TimestampContainerWidget();
    TimestampContainerWidget (const std::vector<SafePointer<TimestampWidget>>& timestampWidgetPtrVector);
    ~TimestampContainerWidget();

    void paint (Graphics&) override;
    void resized() override;

    void addTimestampWidget (const double& timeInSeconds);
    void cleanTimestampVector();
    void flexBoxRelayout();

private:
    std::vector<SafePointer<TimestampWidget>> timestampWidgetPtrVector;
    std::unique_ptr<Viewport> viewportPtr;

    void sortTimestampWidget();
    void a (const TimestampWidget& a, const TimestampWidget& b);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimestampContainerWidget)
};
