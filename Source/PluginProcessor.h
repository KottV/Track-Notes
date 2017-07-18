/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class TrackNotesAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TrackNotesAudioProcessor();
    ~TrackNotesAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    bool twentyMinutesHavePassed();
    void eraseTextAndRemindOfDemo();
    
    // Shouldn't be declaring these at public
    // But I'm having issues with making getter methods, oddly enough
    TextEditor performersNameEditor;
    TextEditor instrumentPlayedEditor;
    TextEditor microphonesUsedEditor;
    TextEditor timestampedNotesEditor;
    TextEditor generalNotesEditor;
    
    File imageOnePath, imageTwoPath;
    Image imageOne, imageTwo;
    bool imageOneMissing, imageTwoMissing;
    
    AudioPlayHead::CurrentPositionInfo positionInformation;
    Label performersNameLabel, instrumentPlayedLabel, microphonesUsedLabel;
    
    int64 startingTime, timeElapsed;
    bool pluginIsRunningInDemoMode;
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackNotesAudioProcessor)
};
