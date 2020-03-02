/*
  ==============================================================================

    TimestampWidget.h
    Created: 1 Mar 2020 12:03:54am
    Author:  Joseph Lyons

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StaticTextSizeButton.hpp"
#include "Timecode.h"

//==============================================================================
/*
*/
class TimestampWidget    : public Component,
                           public Button::Listener
{
public:
    TimestampWidget (const double& timeInSeconds);
    ~TimestampWidget();

    bool operator< (const TimestampWidget& timestampWidgetRight);

    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked (Button* buttonThatWasClicked) override;
    bool getShouldDeleteTimestamp();

private:
    std::unique_ptr<Label> timestampLabelPtr;
    std::unique_ptr<TextEditor> timestampNotesPtr;
    std::unique_ptr<TextButton> removeTimestampButtonPtr;

    std::unique_ptr<StaticTextSizeButton> staticTextSizeButtonPtr;

    Timecode timecode;
    bool shouldDeleteTimestamp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimestampWidget)
};
