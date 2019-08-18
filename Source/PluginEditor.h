/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "StaticTextSizeButton.hpp"
#include "PluginProcessor.h"
#include "BasicWindow.cpp"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TrackNotesAudioProcessorEditor  : public AudioProcessorEditor,
                                        public TextEditor::Listener,
                                        public Button::Listener
{
public:
    //==============================================================================
    TrackNotesAudioProcessorEditor (TrackNotesAudioProcessor &p);
    ~TrackNotesAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void setupVersionNumberlabel();
    void loadImage(Image &image, File &imagePath, const bool &isImageOne);
    void createImageWindow(SafePointer<BasicWindow> &basicWindowPtr, Image &image, File &imagePath);
    void showErrorLoadingImageWindow(const String &path);
    void fillTimeIntervalValues(int &hours, int &minutes, int &seconds);
    String formatAndBuildTimecode(const int &hours, const int &minutes, const int &seconds);
    String formatTimeInterval(const int &timeInterval);
    void createImagePreview(const bool &isImageOne);
    void scaleImageDimensionsIfTooLarge(int &imageWidtht, int &imageHeight);
    void activateStealthMode();
    void deactivateStealthMode();
    void hideTextAndDisableEditor(TextEditor &textEditor);
    void showTextAndEnableEditor(TextEditor &textEditor);
    void setFocusTabOrder();


    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void mouseMove (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    TrackNotesAudioProcessor& processor;
    String versionNumberString;
    Array<Font> usersFontsResults;
    
    ImageComponent imagePreviewOne, imagePreviewTwo;

    bool pluginIsRunningInDemoMode;
    bool *stealthIsActivatedPtr;

    SafePointer<TextEditor> performersNameEditorPtr;
    SafePointer<TextEditor> instrumentPlayedEditorPtr;
    SafePointer<TextEditor> microphonesUsedEditorPtr;
    SafePointer<TextEditor> timestampedNotesEditorPtr;
    SafePointer<TextEditor> generalNotesEditorPtr;

    SafePointer<Label> performersNameLabelPtr;
    SafePointer<Label> instrumentPlayedLabelPtr;
    SafePointer<Label> microphonesUsedLabelPtr;

    SafePointer<BasicWindow> basicWindowImageOnePtr;
    SafePointer<BasicWindow> basicWindowImageTwoPtr;
    
    std::unique_ptr<StaticTextSizeButton> staticTextSizeButtonPtr;

    AudioPlayHead::CurrentPositionInfo *positionInformationPtr;

    TooltipWindow toolTipWindow;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> trackNotesLabel;
    std::unique_ptr<Label> timestampedNotesLabel;
    std::unique_ptr<TextButton> insertTimeStampButton;
    std::unique_ptr<Label> theLyonsDenSoftwareLabel;
    std::unique_ptr<Label> generalNotesLabel;
    std::unique_ptr<TextButton> displayImageOneButton;
    std::unique_ptr<TextButton> displayImageTwoButton;
    std::unique_ptr<TextButton> loadImageOneButton;
    std::unique_ptr<TextButton> loadImageTwoButton;
    std::unique_ptr<TextButton> removeImageOneButton;
    std::unique_ptr<TextButton> removeImageTwoButton;
    std::unique_ptr<Label> imagesLabel;
    std::unique_ptr<TextButton> exportMediaButton;
    std::unique_ptr<TextButton> stealthModeToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackNotesAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

