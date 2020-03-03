/*
  ==============================================================================

    Timecode.cpp
    Created: 1 Mar 2020 2:12:00am
    Author:  Joseph Lyons

  ==============================================================================
*/

#include "Timecode.h"

Timecode::Timecode (const double& timeInSeconds)
{
    buildTimecodeString (timeInSeconds);
}

Timecode::~Timecode()
{
}

bool Timecode::operator< (const Timecode& timecodeRight) const
{
    return timeInSeconds < timecodeRight.timeInSeconds;
}

// This is public in the case that I add the functioanlity to reset the timestamp to a new time
void Timecode::buildTimecodeString (double timeInSeconds)
{
    this->timeInSeconds = timeInSeconds;

    // Calculate hours
    const int SECONDS_PER_HOUR = 3600;
    unsigned int hours = timeInSeconds / SECONDS_PER_HOUR;

    // Deduct hours (in seconds) from total
    timeInSeconds -= (hours * SECONDS_PER_HOUR);

    // Calculate minutes
    const int SECONDS_PER_MINUTE = 60;
    unsigned int minutes = timeInSeconds / SECONDS_PER_MINUTE;

    // Deduct minutes (in seconds) from total
    timeInSeconds -= (minutes * SECONDS_PER_MINUTE);

    // Leftover is seconds
    unsigned int seconds = timeInSeconds;

    timecodeString.clear();
    timecodeString = "@ ";
    timecodeString += String (hours).paddedLeft ('0', 2);
    timecodeString += ":";
    timecodeString += String (minutes).paddedLeft ('0', 2);
    timecodeString += ":";
    timecodeString += String (seconds).paddedLeft ('0', 2);
}

String Timecode::getTimecodeString() const
{
    return timecodeString;
}
