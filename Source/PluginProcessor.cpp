/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


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
    // Point TextEditors Ptrs of editor class to actual GUI TextEditors in processor class
    performersNameEditor.setMultiLine (false);
    performersNameEditor.setReturnKeyStartsNewLine (false);
    performersNameEditor.setReadOnly (false);
    performersNameEditor.setScrollbarsShown (true);
    performersNameEditor.setCaretVisible (true);
    performersNameEditor.setPopupMenuEnabled (true);
    performersNameEditor.setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    performersNameEditor.setColour (TextEditor::highlightColourId, Colours::black);
    performersNameEditor.setColour (TextEditor::outlineColourId, Colour (0xff565454));

    instrumentPlayedEditor.setMultiLine (false);
    instrumentPlayedEditor.setReturnKeyStartsNewLine (false);
    instrumentPlayedEditor.setReadOnly (false);
    instrumentPlayedEditor.setScrollbarsShown (true);
    instrumentPlayedEditor.setCaretVisible (true);
    instrumentPlayedEditor.setPopupMenuEnabled (true);
    instrumentPlayedEditor.setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    instrumentPlayedEditor.setColour (TextEditor::highlightColourId, Colours::black);
    instrumentPlayedEditor.setColour (TextEditor::outlineColourId, Colour (0xff565454));
    
    microphonesUsedEditor.setMultiLine (false);
    microphonesUsedEditor.setReturnKeyStartsNewLine (false);
    microphonesUsedEditor.setReadOnly (false);
    microphonesUsedEditor.setScrollbarsShown (true);
    microphonesUsedEditor.setCaretVisible (true);
    microphonesUsedEditor.setPopupMenuEnabled (true);
    microphonesUsedEditor.setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    microphonesUsedEditor.setColour (TextEditor::highlightColourId, Colours::black);
    microphonesUsedEditor.setColour (TextEditor::outlineColourId, Colour (0xff565454));
    
    timestampedNotesEditor.setMultiLine (true);
    timestampedNotesEditor.setReturnKeyStartsNewLine (true);
    timestampedNotesEditor.setReadOnly (false);
    timestampedNotesEditor.setScrollbarsShown (true);
    timestampedNotesEditor.setCaretVisible (true);
    timestampedNotesEditor.setPopupMenuEnabled (true);
    timestampedNotesEditor.setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    timestampedNotesEditor.setColour (TextEditor::highlightColourId, Colours::black);
    timestampedNotesEditor.setColour (TextEditor::outlineColourId, Colour (0xff565454));
    
    generalNotesEditor.setMultiLine (true);
    generalNotesEditor.setReturnKeyStartsNewLine (true);
    generalNotesEditor.setReadOnly (false);
    generalNotesEditor.setScrollbarsShown (true);
    generalNotesEditor.setCaretVisible (true);
    generalNotesEditor.setPopupMenuEnabled (true);
    generalNotesEditor.setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    generalNotesEditor.setColour (TextEditor::highlightColourId, Colours::black);
    generalNotesEditor.setColour (TextEditor::outlineColourId, Colour (0xff565454));
    
    // Set up text editor font sizes
    int fontSize = 20;
    performersNameEditor.setFont(fontSize);
    instrumentPlayedEditor.setFont(fontSize);
    microphonesUsedEditor.setFont(fontSize);
    timestampedNotesEditor.setFont(fontSize);
    generalNotesEditor.setFont(fontSize);
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
    XmlElement xml ("trackNotes");
    
    // add some attributes to it..
    xml.setAttribute ("performersName", performersNameEditor.getText());
    xml.setAttribute ("instrumentPlayed", instrumentPlayedEditor.getText());
    xml.setAttribute ("microphonesUsed", microphonesUsedEditor.getText());
    xml.setAttribute ("timestampedNotes", timestampedNotesEditor.getText());
    xml.setAttribute ("generalNotes", generalNotesEditor.getText());
    xml.setAttribute ("imageOnePath", imageOnePath.getFullPathName());
    xml.setAttribute ("imageTwoPath", imageTwoPath.getFullPathName());
    
    // Store the values of all our parameters, using their param ID as the XML attribute
    for (int i = 0; i < getNumParameters(); ++i)
        if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
            xml.setAttribute (p->paramID, p->getValue());
    
    // Use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void TrackNotesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
    
    if (xml != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xml->hasTagName ("trackNotes"))
        {
            // ok, now pull our strings
            performersNameEditor.setText(xml->getStringAttribute("performersName"));
            instrumentPlayedEditor.setText(xml->getStringAttribute("instrumentPlayed"));
            microphonesUsedEditor.setText(xml->getStringAttribute("microphonesUsed"));
            timestampedNotesEditor.setText(xml->getStringAttribute("timestampedNotes"));
            generalNotesEditor.setText(xml->getStringAttribute("generalNotes"));
            imageOnePath = xml->getStringAttribute("imageOnePath");
            imageTwoPath = xml->getStringAttribute("imageTwoPath");
            
            // Get string containing path and check to see if its empty or not
            if(!imageOnePath.getFullPathName().isEmpty())
            {
                // If it exists, load it
                if(imageOnePath.exists())
                {
                    imageOneMissing = false;
                    imageOne = ImageCache::getFromFile(imageOnePath);
                }
                
                // If not, then the file has been moved and an error should display
                else
                {
                    imageOneMissing = true;
                }
            }
            
            // Get string containing path and check to see if its empty or not
            if(!imageTwoPath.getFullPathName().isEmpty())
            {
                // If it exists, load it
                if(imageTwoPath.exists())
                {
                    imageTwoMissing = false;
                    imageTwo = ImageCache::getFromFile(imageTwoPath);
                }
                
                // If not, then the file has been moved and an error should display
                else
                {
                    imageTwoMissing = true;
                }
            }
            
            // Now reload our parameters..
            for (int i = 0; i < getNumParameters(); ++i)
                if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
                    p->setValue ((float) xml->getDoubleAttribute (p->paramID, p->getValue()));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TrackNotesAudioProcessor();
}
