/*
  ==============================================================================

    Timestamp.h
    Created: 1 Mar 2020 12:03:54am
    Author:  Joseph Lyons

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StaticTextSizeButton.hpp"
#include "Timecode.h"
#include "TimestampData.h"

//==============================================================================
/*
*/
class Timestamp    : public Component,
                           public Button::Listener
{
public:
    Timestamp (const double& timeInSeconds, const String& notes = String());
    ~Timestamp();

    bool operator< (const Timestamp& TimestampRight) const;

    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked (Button* buttonThatWasClicked) override;

    TimestampData getTimestampData() const;

    void setNotes (const String& notesString);

private:
    std::unique_ptr<Label> timecodeLabelPtr;
    std::unique_ptr<TextEditor> notesPtr;
    std::unique_ptr<TextButton> removeTimestampButtonPtr;

//    std::unique_ptr<StaticTextSizeButton> staticTextSizeButtonPtr;

    Timecode timecode;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Timestamp)
};
