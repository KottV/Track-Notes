/*
 ==============================================================================
 Copyright 2013-2017 Joseph Lyons
 
 This file is part of Track Notes.
 
 Track Notes is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Track Notes is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Track Notes.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "XMLKeyNames.hpp"


//==============================================================================
TrackNotesAudioProcessor::TrackNotesAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TrackNotesAudioProcessor::~TrackNotesAudioProcessor()
{
}

//==============================================================================
const String TrackNotesAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TrackNotesAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TrackNotesAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double TrackNotesAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TrackNotesAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TrackNotesAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TrackNotesAudioProcessor::setCurrentProgram (int index)
{
}

const String TrackNotesAudioProcessor::getProgramName (int index)
{
    return {};
}

void TrackNotesAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TrackNotesAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TrackNotesAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TrackNotesAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false; 

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TrackNotesAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // Pass struct and fill it in with playhead position information
    getPlayHead()->getCurrentPosition (positionInformation);
}

//==============================================================================
bool TrackNotesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TrackNotesAudioProcessor::createEditor()
{
    return new TrackNotesAudioProcessorEditor (*this);
}

//==============================================================================
void TrackNotesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Create an outer XML element..
    XmlElement xml (XMLKeyNames::name);
    
    // add some attributes to it..
    // Also, trim text of editors to keep from saving newlines that may be added during stealth mode
    xml.setAttribute (XMLKeyNames::performersName, performersNameString);
    xml.setAttribute (XMLKeyNames::instrumentPlayed, instrumentPlayedString);
    xml.setAttribute (XMLKeyNames::microphonesUsed, microphonesUsedString);
    xml.setAttribute (XMLKeyNames::timestampedNotes, timestampedNotesString.trim());
    xml.setAttribute (XMLKeyNames::generalNotes, generalNotesString.trim());

    xml.setAttribute (XMLKeyNames::imageOnePath, imageOnePath.getFullPathName());
    xml.setAttribute (XMLKeyNames::imageTwoPath, imageTwoPath.getFullPathName());

    xml.setAttribute (XMLKeyNames::performersNameLabel, performersNameLabelString);
    xml.setAttribute (XMLKeyNames::instrumentPlayedLabel, instrumentPlayedLabelString);
    xml.setAttribute (XMLKeyNames::microphonesUsedLabel, microphonesUsedLabelString);

    xml.setAttribute (XMLKeyNames::stealthIsActivated, stealthIsActivated);

    // Save Timestamp widget data
    xml.setAttribute (XMLKeyNames::numberOfTimestamps, timestampData.size());

    for (int i = 0; i < timestampData.size(); i++)
    {
        xml.setAttribute (XMLKeyNames::timestampsTimeInSecondsBaseName + String(i), timestampData[i].first);
        xml.setAttribute (XMLKeyNames::timestampedNotes + String(i), timestampData[i].second);
    }

    // Use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void TrackNotesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    std::unique_ptr<XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
    
    if (xml != nullptr)
    {
        // Make sure that it's the correct XML file
        if (xml->hasTagName (XMLKeyNames::name))
        {
            // Retrieve editor strings
            performersNameString = xml->getStringAttribute (XMLKeyNames::performersName);
            instrumentPlayedString = xml->getStringAttribute (XMLKeyNames::instrumentPlayed);
            microphonesUsedString = xml->getStringAttribute (XMLKeyNames::microphonesUsed);
            timestampedNotesString = xml->getStringAttribute (XMLKeyNames::timestampedNotes);
            generalNotesString = xml->getStringAttribute (XMLKeyNames::generalNotes);

            imageOnePath = xml->getStringAttribute (XMLKeyNames::imageOnePath);
            imageTwoPath = xml->getStringAttribute (XMLKeyNames::imageTwoPath);

            performersNameLabelString = xml->getStringAttribute (XMLKeyNames::performersNameLabel);
            instrumentPlayedLabelString = xml->getStringAttribute (XMLKeyNames::instrumentPlayedLabel);
            microphonesUsedLabelString = xml->getStringAttribute (XMLKeyNames::microphonesUsedLabel);
            
            stealthIsActivated = xml->getBoolAttribute (XMLKeyNames::stealthIsActivated, false);
            
            // Retrieve paths to images
            if (imageOnePath.exists())
                imageOne = ImageCache::getFromFile (imageOnePath);

            if (imageTwoPath.exists())
                imageTwo = ImageCache::getFromFile (imageTwoPath);

            // Load Timestamp widget data
            int numberOfTimestamps = xml->getIntAttribute (XMLKeyNames::numberOfTimestamps);

            for (int i = 0; i < numberOfTimestamps; i++)
            {
                std::pair<double, String> pair;
                pair.first = xml->getDoubleAttribute (XMLKeyNames::timestampsTimeInSecondsBaseName + String(i));
                pair.second = xml->getStringAttribute (XMLKeyNames::timestampedNotes + String(i));
                timestampData.add (pair);
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TrackNotesAudioProcessor();
}
