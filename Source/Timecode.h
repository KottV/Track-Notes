/*
  ==============================================================================

    Timecode.h
    Created: 1 Mar 2020 2:12:00am
    Author:  Joseph Lyons

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Timecode
{
public:
    Timecode (const double& timeInSeconds);
    ~Timecode();

    bool operator< (const Timecode& timecodeRight);

    void buildTimecodeString (double timeInSeconds);
    String getTimecodeString();
private:
    String timecodeString;

    double timeInSeconds;
};
