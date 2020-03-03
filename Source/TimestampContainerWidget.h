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
    ~TimestampContainerWidget();

    void paint (Graphics&) override;
    void resized() override;

    void addTimestampWidget (const double& timeInSeconds);
    void cleanTimestampVector();
    void deleteChild (TimestampWidget* child);

private:
    OwnedArray<TimestampWidget> timestampWidgetOwnedArray;
    std::unique_ptr<Viewport> viewportPtr;

    void sortTimestampWidget();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimestampContainerWidget)
};
