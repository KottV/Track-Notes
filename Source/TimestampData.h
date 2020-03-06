/*
  ==============================================================================

    TimestampData.h
    Created: 6 Mar 2020 1:42:20pm
    Author:  Joseph Lyons

  ==============================================================================
*/

#pragma once

struct TimestampData
{
    double timeInSeconds;
    String timecodeString;
    String notes;

    TimestampData()
    {
        timeInSeconds = 0;
        timecodeString = String();
        notes = String();
    }
};
