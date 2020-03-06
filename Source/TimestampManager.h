/*
  ==============================================================================

    TimestampManager.h
    Created: 1 Mar 2020 4:42:09pm
    Author:  Joseph Lyons

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Timestamp.h"

//==============================================================================
/*
*/

class TimestampElementComparator
{
public:
    static int compareElements (Timestamp* firstPtr, Timestamp* secondPtr)
    {
        return (*firstPtr < *secondPtr) ? -1 : ((*secondPtr < *firstPtr) ? 1 : 0);
    }
};


class TimestampManager    : public Component
{
public:
    TimestampManager (const unsigned int& width, const unsigned int& height);
    ~TimestampManager();

    void paint (Graphics&) override;
    void resized() override;

    void addTimestamp (const double& timeInSeconds, const String& notes = String());
    void deleteChild (Timestamp* child);

    Array<std::pair<double, String>> getData() const;

private:
    OwnedArray<Timestamp> timestampOwnedArray;
    TimestampElementComparator timestampElementComparator;

    Rectangle<int> layoutRectangle;

    const unsigned int HEIGHT_OF_TIMESTAMP_WIDGETS;
    const unsigned int WIDTH;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimestampManager)
};
