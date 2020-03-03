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

class TimestampElementComparator
{
public:
    static int compareElements (TimestampWidget* firstPtr, TimestampWidget* secondPtr)
    {
        return (*firstPtr < *secondPtr) ? -1 : ((*secondPtr < *firstPtr) ? 1 : 0);
    }
};


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
    TimestampElementComparator timestampElementComparator;
    std::unique_ptr<Viewport> viewportPtr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimestampContainerWidget)
};
