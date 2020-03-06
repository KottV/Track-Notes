/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
#include "ImageWindow.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TrackNotesAudioProcessorEditor::TrackNotesAudioProcessorEditor (TrackNotesAudioProcessor &p)
    : AudioProcessorEditor (&p), processor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..

    createImagePreviews();

    isRunningInDemoMode = true;

    if (isRunningInDemoMode)
    {
        randomNumberGenerator.setSeed (Time::currentTimeMillis());
        startDemoTimer();
    }

    //[/Constructor_pre]

    trackNotesLabel.reset (new Label ("trackNotesLabel",
                                      TRANS("Track Notes")));
    addAndMakeVisible (trackNotesLabel.get());
    trackNotesLabel->setFont (Font ("Arial", 48.70f, Font::plain).withTypefaceStyle ("Regular"));
    trackNotesLabel->setJustificationType (Justification::centredTop);
    trackNotesLabel->setEditable (false, false, false);
    trackNotesLabel->setColour (Label::textColourId, Colours::white);
    trackNotesLabel->setColour (TextEditor::textColourId, Colours::black);
    trackNotesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    trackNotesLabel->setBounds (0, 0, 1005, 50);

    timestampedNotesLabel.reset (new Label ("timestampedNotesLabel",
                                            TRANS("Timestamped Notes:")));
    addAndMakeVisible (timestampedNotesLabel.get());
    timestampedNotesLabel->setFont (Font ("Arial", 25.00f, Font::plain).withTypefaceStyle ("Regular"));
    timestampedNotesLabel->setJustificationType (Justification::centredLeft);
    timestampedNotesLabel->setEditable (false, false, false);
    timestampedNotesLabel->setColour (TextEditor::textColourId, Colours::black);
    timestampedNotesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    timestampedNotesLabel->setBounds (0, 165, 218, 30);

    insertTimeStampButton.reset (new TextButton ("insertTimeStampButton"));
    addAndMakeVisible (insertTimeStampButton.get());
    insertTimeStampButton->setButtonText (TRANS("Insert Timestamp"));
    insertTimeStampButton->addListener (this);
    insertTimeStampButton->setColour (TextButton::buttonColourId, Colour (0xff393939));

    insertTimeStampButton->setBounds (218, 165, 282, 30);

    theLyonsDenSoftwareLabel.reset (new Label ("theLyonsDenSoftwareLabel",
                                               String()));
    addAndMakeVisible (theLyonsDenSoftwareLabel.get());
    theLyonsDenSoftwareLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    theLyonsDenSoftwareLabel->setJustificationType (Justification::centredLeft);
    theLyonsDenSoftwareLabel->setEditable (false, false, false);
    theLyonsDenSoftwareLabel->setColour (TextEditor::textColourId, Colours::black);
    theLyonsDenSoftwareLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    theLyonsDenSoftwareLabel->setBounds (0, 590, 500, 30);

    generalNotesLabel.reset (new Label ("generalNotesLabel",
                                        TRANS("General Notes:")));
    addAndMakeVisible (generalNotesLabel.get());
    generalNotesLabel->setFont (Font ("Arial", 25.00f, Font::plain).withTypefaceStyle ("Regular"));
    generalNotesLabel->setJustificationType (Justification::centred);
    generalNotesLabel->setEditable (false, false, false);
    generalNotesLabel->setColour (TextEditor::textColourId, Colours::black);
    generalNotesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    generalNotesLabel->setBounds (0, 380, 1005, 30);

    displayImageOneButton.reset (new TextButton ("displayImageOneButton"));
    addAndMakeVisible (displayImageOneButton.get());
    displayImageOneButton->setButtonText (TRANS("Empty"));
    displayImageOneButton->addListener (this);
    displayImageOneButton->setColour (TextButton::buttonColourId, Colour (0xff393939));

    displayImageOneButton->setBounds (560, 95, 145, 30);

    displayImageTwoButton.reset (new TextButton ("displayImageTwoButton"));
    addAndMakeVisible (displayImageTwoButton.get());
    displayImageTwoButton->setButtonText (TRANS("Empty"));
    displayImageTwoButton->addListener (this);
    displayImageTwoButton->setColour (TextButton::buttonColourId, Colour (0xff393939));

    displayImageTwoButton->setBounds (810, 95, 145, 30);

    loadImageOneButton.reset (new TextButton ("loadImageOneButton"));
    addAndMakeVisible (loadImageOneButton.get());
    loadImageOneButton->setButtonText (TRANS("Load"));
    loadImageOneButton->addListener (this);
    loadImageOneButton->setColour (TextButton::buttonColourId, Colour (0xff393939));

    loadImageOneButton->setBounds (510, 95, 50, 30);

    loadImageTwoButton.reset (new TextButton ("loadImageTwoButton"));
    addAndMakeVisible (loadImageTwoButton.get());
    loadImageTwoButton->setButtonText (TRANS("Load"));
    loadImageTwoButton->addListener (this);
    loadImageTwoButton->setColour (TextButton::buttonColourId, Colour (0xff393939));

    loadImageTwoButton->setBounds (760, 95, 50, 30);

    removeImageOneButton.reset (new TextButton ("removeImageOneButton"));
    addAndMakeVisible (removeImageOneButton.get());
    removeImageOneButton->setButtonText (TRANS("Remove"));
    removeImageOneButton->addListener (this);
    removeImageOneButton->setColour (TextButton::buttonColourId, Colour (0xff393939));

    removeImageOneButton->setBounds (705, 95, 50, 30);

    removeImageTwoButton.reset (new TextButton ("removeImageTwoButton"));
    addAndMakeVisible (removeImageTwoButton.get());
    removeImageTwoButton->setButtonText (TRANS("Remove"));
    removeImageTwoButton->addListener (this);
    removeImageTwoButton->setColour (TextButton::buttonColourId, Colour (0xff393939));

    removeImageTwoButton->setBounds (955, 95, 50, 30);

    imagesLabel.reset (new Label ("imagesLabel",
                                  TRANS("Images:")));
    addAndMakeVisible (imagesLabel.get());
    imagesLabel->setFont (Font ("Arial", 25.00f, Font::plain).withTypefaceStyle ("Regular"));
    imagesLabel->setJustificationType (Justification::centred);
    imagesLabel->setEditable (false, false, false);
    imagesLabel->setColour (TextEditor::textColourId, Colours::black);
    imagesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    imagesLabel->setBounds (510, 60, 500, 30);

    exportMediaButton.reset (new TextButton ("exportMediaButton"));
    addAndMakeVisible (exportMediaButton.get());
    exportMediaButton->setButtonText (TRANS("Export Media"));
    exportMediaButton->addListener (this);
    exportMediaButton->setColour (TextButton::buttonColourId, Colour (0xff393939));
    exportMediaButton->setColour (TextButton::textColourOnId, Colours::white);

    exportMediaButton->setBounds (805, 595, 200, 20);

    stealthModeToggle.reset (new TextButton ("stealthModeToggle"));
    addAndMakeVisible (stealthModeToggle.get());
    stealthModeToggle->setTooltip (TRANS("This button activates \"Stealth Mode.\"  We may not always want to show the clients the notes we write about their performances, so when this button is engaged, Timestamped Notes and General Notes are hidden.  Additionally, it also deactivates the \"Insert Timestamp\" button."));
    stealthModeToggle->setButtonText (String());
    stealthModeToggle->addListener (this);
    stealthModeToggle->setColour (TextButton::buttonColourId, Colour (0xff393939));
    stealthModeToggle->setColour (TextButton::buttonOnColourId, Colours::white);
    stealthModeToggle->setColour (TextButton::textColourOnId, Colours::black);

    stealthModeToggle->setBounds (752, 595, 48, 20);

    performersNameLabel.reset (new Label ("performersNameLabel",
                                          TRANS("Performer\'s Name:")));
    addAndMakeVisible (performersNameLabel.get());
    performersNameLabel->setFont (Font ("Arial", 25.00f, Font::plain).withTypefaceStyle ("Regular"));
    performersNameLabel->setJustificationType (Justification::centredLeft);
    performersNameLabel->setEditable (false, false, false);
    performersNameLabel->setColour (TextEditor::textColourId, Colours::black);
    performersNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    performersNameLabel->setBounds (0, 60, 218, 30);

    instrumentPlayedLabel.reset (new Label ("instrumentPlayedLabel",
                                            TRANS("Instrument Played:")));
    addAndMakeVisible (instrumentPlayedLabel.get());
    instrumentPlayedLabel->setFont (Font ("Arial", 25.00f, Font::plain).withTypefaceStyle ("Regular"));
    instrumentPlayedLabel->setJustificationType (Justification::centredLeft);
    instrumentPlayedLabel->setEditable (false, false, false);
    instrumentPlayedLabel->setColour (TextEditor::textColourId, Colours::black);
    instrumentPlayedLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    instrumentPlayedLabel->setBounds (0, 95, 218, 30);

    microphonesUsedLabel.reset (new Label ("microphonesUsedLabel",
                                           TRANS("Microphone(s) Used:")));
    addAndMakeVisible (microphonesUsedLabel.get());
    microphonesUsedLabel->setFont (Font ("Arial", 25.00f, Font::plain).withTypefaceStyle ("Regular"));
    microphonesUsedLabel->setJustificationType (Justification::centredLeft);
    microphonesUsedLabel->setEditable (false, false, false);
    microphonesUsedLabel->setColour (TextEditor::textColourId, Colours::black);
    microphonesUsedLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    microphonesUsedLabel->setBounds (0, 130, 218, 30);

    performersNameEditor.reset (new TextEditor ("performersNameEditor"));
    addAndMakeVisible (performersNameEditor.get());
    performersNameEditor->setMultiLine (false);
    performersNameEditor->setReturnKeyStartsNewLine (false);
    performersNameEditor->setReadOnly (false);
    performersNameEditor->setScrollbarsShown (false);
    performersNameEditor->setCaretVisible (true);
    performersNameEditor->setPopupMenuEnabled (true);
    performersNameEditor->setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    performersNameEditor->setColour (TextEditor::highlightColourId, Colours::black);
    performersNameEditor->setColour (TextEditor::outlineColourId, Colour (0xff565454));
    performersNameEditor->setText (String());

    performersNameEditor->setBounds (218, 60, 282, 30);

    instrumentPlayedEditor.reset (new TextEditor ("instrumentPlayedEditor"));
    addAndMakeVisible (instrumentPlayedEditor.get());
    instrumentPlayedEditor->setMultiLine (false);
    instrumentPlayedEditor->setReturnKeyStartsNewLine (false);
    instrumentPlayedEditor->setReadOnly (false);
    instrumentPlayedEditor->setScrollbarsShown (false);
    instrumentPlayedEditor->setCaretVisible (true);
    instrumentPlayedEditor->setPopupMenuEnabled (true);
    instrumentPlayedEditor->setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    instrumentPlayedEditor->setColour (TextEditor::highlightColourId, Colours::black);
    instrumentPlayedEditor->setColour (TextEditor::outlineColourId, Colour (0xff565454));
    instrumentPlayedEditor->setText (String());

    instrumentPlayedEditor->setBounds (218, 95, 282, 30);

    microphonesUsedEditor.reset (new TextEditor ("microphonesUsedEditor"));
    addAndMakeVisible (microphonesUsedEditor.get());
    microphonesUsedEditor->setMultiLine (false);
    microphonesUsedEditor->setReturnKeyStartsNewLine (false);
    microphonesUsedEditor->setReadOnly (false);
    microphonesUsedEditor->setScrollbarsShown (false);
    microphonesUsedEditor->setCaretVisible (true);
    microphonesUsedEditor->setPopupMenuEnabled (true);
    microphonesUsedEditor->setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    microphonesUsedEditor->setColour (TextEditor::highlightColourId, Colours::black);
    microphonesUsedEditor->setColour (TextEditor::outlineColourId, Colour (0xff565454));
    microphonesUsedEditor->setText (String());

    microphonesUsedEditor->setBounds (218, 130, 282, 30);

    timestampedNotesEditor.reset (new TextEditor ("timestampedNotesEditor"));
    addAndMakeVisible (timestampedNotesEditor.get());
    timestampedNotesEditor->setMultiLine (true);
    timestampedNotesEditor->setReturnKeyStartsNewLine (true);
    timestampedNotesEditor->setReadOnly (false);
    timestampedNotesEditor->setScrollbarsShown (true);
    timestampedNotesEditor->setCaretVisible (true);
    timestampedNotesEditor->setPopupMenuEnabled (true);
    timestampedNotesEditor->setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    timestampedNotesEditor->setColour (TextEditor::highlightColourId, Colours::black);
    timestampedNotesEditor->setColour (TextEditor::outlineColourId, Colour (0xff565454));
    timestampedNotesEditor->setText (String());

    timestampedNotesEditor->setBounds (0, 200, 500, 175);

    generalNotesEditor.reset (new TextEditor ("generalNotesEditor"));
    addAndMakeVisible (generalNotesEditor.get());
    generalNotesEditor->setMultiLine (true);
    generalNotesEditor->setReturnKeyStartsNewLine (true);
    generalNotesEditor->setReadOnly (false);
    generalNotesEditor->setScrollbarsShown (true);
    generalNotesEditor->setCaretVisible (true);
    generalNotesEditor->setPopupMenuEnabled (true);
    generalNotesEditor->setColour (TextEditor::backgroundColourId, Colour (0xff565454));
    generalNotesEditor->setColour (TextEditor::highlightColourId, Colours::black);
    generalNotesEditor->setColour (TextEditor::outlineColourId, Colour (0xff565454));
    generalNotesEditor->setText (String());

    generalNotesEditor->setBounds (0, 415, 1010, 175);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1005, 620);


    //[Constructor] You can add your own custom stuff here..

    // Set up text editor font sizes
    const int fontSize = 20;

    performersNameEditor->setFont (fontSize);
    instrumentPlayedEditor->setFont (fontSize);
    microphonesUsedEditor->setFont (fontSize);
    timestampedNotesEditor->setFont (fontSize);
    generalNotesEditor->setFont (fontSize);

    getDataFromProcessor();

    // Reset button names to image name (this doesn't work in standalone
    // since constructor isn't called when standalone loads, because plugin is already open
    if (processor.imageOnePath.getFullPathName().isNotEmpty())
        displayImageOneButton->setButtonText (processor.imageOnePath.getFileNameWithoutExtension());

    if (processor.imageTwoPath.getFullPathName().isNotEmpty())
        displayImageTwoButton->setButtonText (processor.imageTwoPath.getFileNameWithoutExtension());

    setupVersionNumberlabel();

    // Get array of fonts on user's system
    Font::findFonts (usersFontsResults);

    // Set up labels
    performersNameLabel->setEditable (true);
    instrumentPlayedLabel->setEditable (true);
    microphonesUsedLabel->setEditable (true);

    // Add label listeners
    performersNameLabel->addListener (this);
    instrumentPlayedLabel->addListener (this);
    microphonesUsedLabel->addListener (this);

    setDefaultLabelText();

    // Set up static text buttons
    staticTextSizeButtonPtr.reset (new StaticTextSizeButton);

    loadImageOneButton->setLookAndFeel (staticTextSizeButtonPtr.get());
    displayImageOneButton->setLookAndFeel (staticTextSizeButtonPtr.get());
    removeImageOneButton->setLookAndFeel (staticTextSizeButtonPtr.get());
    loadImageTwoButton->setLookAndFeel (staticTextSizeButtonPtr.get());
    displayImageTwoButton->setLookAndFeel (staticTextSizeButtonPtr.get());
    removeImageTwoButton->setLookAndFeel (staticTextSizeButtonPtr.get());

    viewportPtr.reset (new Viewport);
    addAndMakeVisible (viewportPtr.get());
    viewportPtr->setBounds (0, 200, 500, 175);

    timestampManagerPtr.reset (new TimestampManager (
        viewportPtr->getWidth(),
        viewportPtr->getHeight())
    );
    addAndMakeVisible (timestampManagerPtr.get());

    viewportPtr->setViewedComponent (timestampManagerPtr.get(), false);
    viewportPtr->setScrollBarsShown (true, false);

    // Set up stealth mode
    // Turn button into a toggle button
    stealthModeToggle->setClickingTogglesState (true);
    setStealthModeState (stealthModeToggle->getToggleState());
    stealthModeToggle->setToggleState (stealthModeToggle->getToggleState(), dontSendNotification);

    // Add mouse listener to this to create dynamic text in button
    stealthModeToggle->addMouseListener (this, true);

    setFocusTabOrder();

    //[/Constructor]
}

TrackNotesAudioProcessorEditor::~TrackNotesAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    saveDataToProcessor();

    // Normal C++ Pointers
    delete basicWindowImageOnePtr;
    delete basicWindowImageTwoPtr;
    basicWindowImageOnePtr = nullptr;
    basicWindowImageTwoPtr = nullptr;

    //[/Destructor_pre]

    trackNotesLabel = nullptr;
    timestampedNotesLabel = nullptr;
    insertTimeStampButton = nullptr;
    theLyonsDenSoftwareLabel = nullptr;
    generalNotesLabel = nullptr;
    displayImageOneButton = nullptr;
    displayImageTwoButton = nullptr;
    loadImageOneButton = nullptr;
    loadImageTwoButton = nullptr;
    removeImageOneButton = nullptr;
    removeImageTwoButton = nullptr;
    imagesLabel = nullptr;
    exportMediaButton = nullptr;
    stealthModeToggle = nullptr;
    performersNameLabel = nullptr;
    instrumentPlayedLabel = nullptr;
    microphonesUsedLabel = nullptr;
    performersNameEditor = nullptr;
    instrumentPlayedEditor = nullptr;
    microphonesUsedEditor = nullptr;
    timestampedNotesEditor = nullptr;
    generalNotesEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    staticTextSizeButtonPtr = nullptr;
    timestampManagerPtr = nullptr;
    viewportPtr = nullptr;

    //[/Destructor]
}

//==============================================================================
void TrackNotesAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff373737));

    {
        int x = 510, y = 130, width = 245, height = 245;
        Colour fillColour = Colour (0xff565454);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 760, y = 130, width = 245, height = 245;
        Colour fillColour = Colour (0xff565454);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..

    g.setColour (Colours::white);
    g.setOpacity (0.3);
    g.drawLine (30, 50, 975, 50, 1);

    //[/UserPaint]
}

void TrackNotesAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TrackNotesAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == insertTimeStampButton.get())
    {
        //[UserButtonCode_insertTimeStampButton] -- add your button handler code here..

        timestampManagerPtr->addTimestamp (processor.positionInformation.timeInSeconds);
        
        //[/UserButtonCode_insertTimeStampButton]
    }
    else if (buttonThatWasClicked == displayImageOneButton.get())
    {
        //[UserButtonCode_displayImageOneButton] -- add your button handler code here..

        if (processor.imageOnePath.getFullPathName().isNotEmpty())
        {
            if (! processor.imageOnePath.exists())
                showErrorLoadingImageWindow (processor.imageOnePath.getFullPathName());
            else
                createImageWindow (basicWindowImageOnePtr, processor.imageOne, processor.imageOnePath);
        }

        //[/UserButtonCode_displayImageOneButton]
    }
    else if (buttonThatWasClicked == displayImageTwoButton.get())
    {
        //[UserButtonCode_displayImageTwoButton] -- add your button handler code here..

        if (processor.imageTwoPath.getFullPathName().isNotEmpty())
        {
            if (! processor.imageTwoPath.exists())
                showErrorLoadingImageWindow (processor.imageTwoPath.getFullPathName());
            else
                createImageWindow (basicWindowImageTwoPtr, processor.imageTwo, processor.imageTwoPath);
        }

        //[/UserButtonCode_displayImageTwoButton]
    }
    else if (buttonThatWasClicked == loadImageOneButton.get())
    {
        //[UserButtonCode_loadImageOneButton] -- add your button handler code here..

        loadImage (processor.imageOne, processor.imageOnePath, true);

        if (! processor.imageOne.isNull())
            displayImageOneButton->setButtonText (processor.imageOnePath.getFileNameWithoutExtension());

        //[/UserButtonCode_loadImageOneButton]
    }
    else if (buttonThatWasClicked == loadImageTwoButton.get())
    {
        //[UserButtonCode_loadImageTwoButton] -- add your button handler code here..

        loadImage (processor.imageTwo, processor.imageTwoPath, false);

        if (! processor.imageTwo.isNull())
            displayImageTwoButton->setButtonText (processor.imageTwoPath.getFileNameWithoutExtension());

        //[/UserButtonCode_loadImageTwoButton]
    }
    else if (buttonThatWasClicked == removeImageOneButton.get())
    {
        //[UserButtonCode_removeImageOneButton] -- add your button handler code here..

        imagePreviewOne.setVisible (false);

        Image blankImage;
        processor.imageOnePath = "";
        processor.imageOne = blankImage;
        displayImageOneButton->setButtonText ("Empty");

        //[/UserButtonCode_removeImageOneButton]
    }
    else if (buttonThatWasClicked == removeImageTwoButton.get())
    {
        //[UserButtonCode_removeImageTwoButton] -- add your button handler code here..

        imagePreviewTwo.setVisible (false);

        Image blankImage;
        processor.imageTwoPath = "";
        processor.imageTwo = blankImage;
        displayImageTwoButton->setButtonText ("Empty");

        //[/UserButtonCode_removeImageTwoButton]
    }
    else if (buttonThatWasClicked == exportMediaButton.get())
    {
        //[UserButtonCode_exportMediaButton] -- add your button handler code here..

        exportMedia();

        //[/UserButtonCode_exportMediaButton]
    }
    else if (buttonThatWasClicked == stealthModeToggle.get())
    {
        //[UserButtonCode_stealthModeToggle] -- add your button handler code here..

        setStealthModeState (stealthModeToggle->getToggleState());

        //[/UserButtonCode_stealthModeToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void TrackNotesAudioProcessorEditor::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...

    if (stealthModeToggle->isMouseOver())
        stealthModeToggle->setButtonText ("Stealth");
    else
        stealthModeToggle->setButtonText ("");

    //[/UserCode_mouseMove]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TrackNotesAudioProcessorEditor::setupVersionNumberlabel()
{
    versionNumberString =  ": ";
    versionNumberString +=  ProjectInfo::projectName;
    versionNumberString += " v";
    versionNumberString += ProjectInfo::versionString;
    versionNumberString += " - ";

    if (isRunningInDemoMode)
        versionNumberString += "Demo";
    else
        versionNumberString += "Full";

    versionNumberString += " Version";

    theLyonsDenSoftwareLabel->setText ("The Lyons' Den Software" + versionNumberString,
                                       dontSendNotification);
}

void TrackNotesAudioProcessorEditor::loadImage (Image &image, File &imagePath, const bool &isImageOne)
{
    FileChooser fileChooser ("Export all Text",
                             File::getSpecialLocation(File::userHomeDirectory),
                             "*",
                             true);


    // Launch browser window and only if they pick a image do we set the image path
    if (fileChooser.browseForFileToOpen())
    {
        // Set imagePath
        imagePath = fileChooser.getResult();

        // Get image
        image = ImageCache::getFromFile (fileChooser.getResult());
    }

    createImagePreviews();
}

void TrackNotesAudioProcessorEditor::createImagePreviews()
{
    imagePreviewOne.setVisible(false);
    imagePreviewOne.setImage(processor.imageOne);
    imagePreviewOne.setBounds(510, 130, 245, 245);
    addAndMakeVisible(imagePreviewOne);

    imagePreviewTwo.setVisible(false);
    imagePreviewTwo.setImage(processor.imageTwo);
    imagePreviewTwo.setBounds(760, 130, 245, 245);
    addAndMakeVisible(imagePreviewTwo);
}

void TrackNotesAudioProcessorEditor::createImageWindow (SafePointer<BasicWindow> &basicWindowPtr,
                                                        Image &image, File &imagePath)
{
    // Don't allow multiple copies of this window to be made
    if (basicWindowPtr == NULL)
    {
        int height = image.getHeight();
        int width  = image.getWidth();
        scaleImageDimensionsIfTooLarge (width, height);

        basicWindowPtr = new BasicWindow (imagePath.getFileNameWithoutExtension(),
                                          Colours::grey,
                                          DocumentWindow::closeButton |
                                          DocumentWindow::minimiseButton);

        basicWindowPtr->setUsingNativeTitleBar (true);
        basicWindowPtr->setContentOwned (new ImageWindow (image, width, height), true);
        basicWindowPtr->setAlwaysOnTop (true);

        if (! image.isNull())
        {
            basicWindowPtr->setSize (width, height);
            basicWindowPtr->centreWithSize (width, height);
        }
        // This should never occur, as this function is not even called when the image doesn't exist
        else
            basicWindowPtr->centreWithSize (basicWindowPtr->getWidth(), basicWindowPtr->getHeight());

        basicWindowPtr->setVisible (true);
    }
    // If window is open already and display button is clicked again, window will be deleted
    else
        delete basicWindowPtr;
}

void TrackNotesAudioProcessorEditor::showErrorLoadingImageWindow (const String &path)
{
    AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                 "Image Missing: ",
                                 path + "\n\nPlease load image again.");
}

void TrackNotesAudioProcessorEditor::scaleImageDimensionsIfTooLarge (int &imageWidth,
                                                                     int &imageHeight)
{
    // Get desktop dimensions
    Rectangle<int> totalArea = Desktop::getInstance().getDisplays().getMainDisplay().totalArea;
    int screenWidth  = totalArea.getWidth();
    int screenHeight = totalArea.getHeight();

    // Trim vertically and horizontally to account for docks, taskbars, menus, and whatnot
    screenWidth  -= 100;
    screenHeight -= 100;

    // Get difference
    int widthDifference  = screenWidth - imageWidth;
    int heightDifference = screenHeight - imageHeight;

    // Leave function if image is smaller than screen size - essentially, do nothing
    if ((widthDifference > 0) && (heightDifference > 0))
        return;

    // Scale the image based on whichever dimension is closer to the edge of the screen.
    // The dimension that is closest to the edge of the screen is the one with the smallest difference.
    if (widthDifference < heightDifference)
    {
        float imageAspectRatio = screenWidth / (float) imageWidth;

        // Set image width to screen width and scale height appropriately
        imageWidth = screenWidth;
        imageHeight *= imageAspectRatio;
    }
    else
    {
        float imageAspectRatio = screenHeight / (float) imageHeight;

        // Set image height to screen height and scale width appropriately
        imageHeight = screenHeight;
        imageWidth *= imageAspectRatio;
    }
}

void TrackNotesAudioProcessorEditor::setStealthModeState (const bool& isActivated)
{
    if (isActivated)
    {
        hideTextAndDisableEditor (*timestampedNotesEditor);
        hideTextAndDisableEditor (*generalNotesEditor);
    }
    else
    {
        showTextAndEnableEditor (*timestampedNotesEditor);
        showTextAndEnableEditor (*generalNotesEditor);
    }

    insertTimeStampButton->setInterceptsMouseClicks (! isActivated, ! isActivated);
}

void TrackNotesAudioProcessorEditor::hideTextAndDisableEditor (TextEditor &textEditor)
{
    unsigned int numberOfLinesVisibleInEditor = (textEditor.getHeight() / textEditor.getFont().getHeight());
    String tempTextHolder = String::repeatedString ("\n", numberOfLinesVisibleInEditor + 1) + textEditor.getText();

    textEditor.setText (tempTextHolder, dontSendNotification);
    textEditor.moveCaretToTop (false);
    textEditor.setScrollbarsShown (false);
    textEditor.setReadOnly (true);
    textEditor.setInterceptsMouseClicks (false, false);
}

void TrackNotesAudioProcessorEditor::showTextAndEnableEditor (TextEditor &textEditor)
{
    String tempTextHolder = textEditor.getText().trimStart();

    textEditor.setText (tempTextHolder);
    textEditor.moveCaretToTop (false);
    textEditor.setScrollbarsShown (true);
    textEditor.setReadOnly (false);
    textEditor.setInterceptsMouseClicks (true, true);
}

void TrackNotesAudioProcessorEditor::setFocusTabOrder()
{
    // Set up tap order
    performersNameEditor->setExplicitFocusOrder (1);
    instrumentPlayedEditor->setExplicitFocusOrder (2);
    microphonesUsedEditor->setExplicitFocusOrder (3);
    timestampedNotesEditor->setExplicitFocusOrder (4);
    generalNotesEditor->setExplicitFocusOrder (5);
    performersNameLabel->setExplicitFocusOrder (6);
    instrumentPlayedLabel->setExplicitFocusOrder (7);
    microphonesUsedLabel->setExplicitFocusOrder (8);

    // Remove keyboard focus from these elements so that they are not included in tap order
    loadImageOneButton->setWantsKeyboardFocus (false);
    displayImageOneButton->setWantsKeyboardFocus (false);
    removeImageOneButton->setWantsKeyboardFocus (false);
    loadImageTwoButton->setWantsKeyboardFocus (false);
    displayImageTwoButton->setWantsKeyboardFocus (false);
    removeImageTwoButton->setWantsKeyboardFocus (false);
    insertTimeStampButton->setWantsKeyboardFocus (false);
    stealthModeToggle->setWantsKeyboardFocus (false);
    exportMediaButton->setWantsKeyboardFocus (false);
}

void TrackNotesAudioProcessorEditor::startDemoTimer()
{
    int minutes      = 20;
    int seconds      = minutes * 60;
    int milliseconds = seconds * 1000;

    startTimer (milliseconds);
}

void TrackNotesAudioProcessorEditor::timerCallback()
{
    int randomNumber = randomNumberGenerator.nextInt(5);
    String demoText = "Track Notes Demo Version.";

    if (randomNumber == 0)
        performersNameEditor->setText (demoText);
    else if (randomNumber == 1)
        instrumentPlayedEditor->setText (demoText);
    else if (randomNumber == 2)
        microphonesUsedEditor->setText (demoText);
    else if (randomNumber == 3)
        timestampedNotesEditor->setText (demoText);
    else
        generalNotesEditor->setText (demoText);
}

void TrackNotesAudioProcessorEditor::getDataFromProcessor()
{
    // Editors
    performersNameEditor->setText (processor.performersNameString);
    instrumentPlayedEditor->setText (processor.instrumentPlayedString);
    microphonesUsedEditor->setText (processor.microphonesUsedString);

    timestampedNotesEditor->setText (processor.timestampedNotesString);
    generalNotesEditor->setText (processor.generalNotesString);

    // Label
    performersNameLabel->setText (processor.performersNameLabelString, dontSendNotification);
    instrumentPlayedLabel->setText (processor.instrumentPlayedLabelString, dontSendNotification);
    microphonesUsedLabel->setText (processor.microphonesUsedLabelString, dontSendNotification);

    // Buttons
    stealthModeToggle->setToggleState(processor.stealthIsActivated, dontSendNotification);
}

void TrackNotesAudioProcessorEditor::saveDataToProcessor()
{
    // Editors
    processor.performersNameString = performersNameEditor->getText();
    processor.instrumentPlayedString = instrumentPlayedEditor->getText();
    processor.microphonesUsedString = microphonesUsedEditor->getText();

    processor.timestampedNotesString = timestampedNotesEditor->getText();
    processor.generalNotesString = generalNotesEditor->getText();

    // Labels
    performersNameLabel->hideEditor (false);
    instrumentPlayedLabel->hideEditor (false);
    microphonesUsedLabel->hideEditor (false);

    processor.performersNameLabelString = performersNameLabel->getText();
    processor.instrumentPlayedLabelString = instrumentPlayedLabel->getText();
    processor.microphonesUsedLabelString = microphonesUsedLabel->getText();

    // Buttons
    processor.stealthIsActivated = stealthModeToggle->getToggleState();
}

void TrackNotesAudioProcessorEditor::labelTextChanged (Label* labelThatHasChanged)
{
    setDefaultLabelText();
}

void TrackNotesAudioProcessorEditor::setDefaultLabelText()
{
    if (performersNameLabel->getText().isEmpty())
        performersNameLabel->setText ("Performer's Name:", dontSendNotification);

    if (instrumentPlayedLabel->getText().isEmpty())
        instrumentPlayedLabel->setText ("Instrument Played:", dontSendNotification);

    if (microphonesUsedLabel->getText().isEmpty())
        microphonesUsedLabel->setText ("Microphone(s) Used:", dontSendNotification);
}

void TrackNotesAudioProcessorEditor::exportMedia()
{
    FileChooser fileChooser ("Export Text",
                             File::getSpecialLocation (File::userHomeDirectory),
                             "*",
                             true);

    if (fileChooser.browseForFileToSave (true))
    {
        // Create folder
        File pathToSaveFolder (fileChooser.getResult());
        pathToSaveFolder.createDirectory();

        // Create path to .txt file with same name as the save folder
        File pathToSaveTextFileTo = pathToSaveFolder;
        pathToSaveTextFileTo = pathToSaveTextFileTo.getFullPathName()
                             + "/"
                             + pathToSaveTextFileTo.getFileName()
                             + ".txt";

        // Save all text and trim text of editors to keep from saving newlines that may be added
        // during stealth mode
        pathToSaveTextFileTo.appendText (performersNameLabel->getText());
        pathToSaveTextFileTo.appendText (" " + performersNameEditor->getText() + "\n\n");

        pathToSaveTextFileTo.appendText (instrumentPlayedLabel->getText());
        pathToSaveTextFileTo.appendText (" " + instrumentPlayedEditor->getText() + "\n\n");

        pathToSaveTextFileTo.appendText (microphonesUsedLabel->getText());
        pathToSaveTextFileTo.appendText (" " + microphonesUsedEditor->getText() + "\n\n");

        pathToSaveTextFileTo.appendText ("Timestamped Notes:\n");
        pathToSaveTextFileTo.appendText (timestampedNotesEditor->getText().trim() + "\n\n");

        pathToSaveTextFileTo.appendText ("General Notes:\n");
        pathToSaveTextFileTo.appendText (generalNotesEditor->getText().trim() + "\n\n");

        pathToSaveTextFileTo.appendText ("Image One: ");
        pathToSaveTextFileTo.appendText (processor.imageOnePath.getFileName() + "\n\n");

        pathToSaveTextFileTo.appendText ("Image Two: ");
        pathToSaveTextFileTo.appendText (processor.imageTwoPath.getFileName());

        // Copy images into folder
        processor.imageOnePath.copyFileTo (pathToSaveFolder.getFullPathName() + "/" +
                                           processor.imageOnePath.getFileName());
        processor.imageTwoPath.copyFileTo (pathToSaveFolder.getFullPathName() + "/" +
                                           processor.imageTwoPath.getFileName());
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TrackNotesAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public TextEditor::Listener, private Timer, public Label::Listener"
                 constructorParams="TrackNotesAudioProcessor &amp;p" variableInitialisers="AudioProcessorEditor (&amp;p), processor (p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1005" initialHeight="620">
  <METHODS>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff373737">
    <RECT pos="510 130 245 245" fill="solid: ff565454" hasStroke="0"/>
    <RECT pos="760 130 245 245" fill="solid: ff565454" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="trackNotesLabel" id="92aa8337c9826f3e" memberName="trackNotesLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 1005 50" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Track Notes" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial"
         fontsize="48.7" kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="timestampedNotesLabel" id="358938facaa251fc" memberName="timestampedNotesLabel"
         virtualName="" explicitFocusOrder="0" pos="0 165 218 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Timestamped Notes:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial"
         fontsize="25.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="insertTimeStampButton" id="2d604f6be40451a7" memberName="insertTimeStampButton"
              virtualName="" explicitFocusOrder="0" pos="218 165 282 30" bgColOff="ff393939"
              buttonText="Insert Timestamp" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="theLyonsDenSoftwareLabel" id="d0cfddad51f6f3" memberName="theLyonsDenSoftwareLabel"
         virtualName="" explicitFocusOrder="0" pos="0 590 500 30" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="generalNotesLabel" id="c170b98fbe39594f" memberName="generalNotesLabel"
         virtualName="" explicitFocusOrder="0" pos="0 380 1005 30" edTextCol="ff000000"
         edBkgCol="0" labelText="General Notes:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial"
         fontsize="25.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="displayImageOneButton" id="a8b273a63654dd33" memberName="displayImageOneButton"
              virtualName="" explicitFocusOrder="0" pos="560 95 145 30" bgColOff="ff393939"
              buttonText="Empty" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="displayImageTwoButton" id="49cbe3c0cc417d1e" memberName="displayImageTwoButton"
              virtualName="" explicitFocusOrder="0" pos="810 95 145 30" bgColOff="ff393939"
              buttonText="Empty" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="loadImageOneButton" id="b3cf03e99303b480" memberName="loadImageOneButton"
              virtualName="" explicitFocusOrder="0" pos="510 95 50 30" bgColOff="ff393939"
              buttonText="Load" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="loadImageTwoButton" id="c76f47c5a5ad9793" memberName="loadImageTwoButton"
              virtualName="" explicitFocusOrder="0" pos="760 95 50 30" bgColOff="ff393939"
              buttonText="Load" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="removeImageOneButton" id="c4e0c098ca1c7a0c" memberName="removeImageOneButton"
              virtualName="" explicitFocusOrder="0" pos="705 95 50 30" bgColOff="ff393939"
              buttonText="Remove" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="removeImageTwoButton" id="6b14eed5f55e2af7" memberName="removeImageTwoButton"
              virtualName="" explicitFocusOrder="0" pos="955 95 50 30" bgColOff="ff393939"
              buttonText="Remove" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="imagesLabel" id="3f296d22943adc31" memberName="imagesLabel"
         virtualName="" explicitFocusOrder="0" pos="510 60 500 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Images:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Arial" fontsize="25.0" kerning="0.0"
         bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="exportMediaButton" id="ab681e4541856006" memberName="exportMediaButton"
              virtualName="" explicitFocusOrder="0" pos="805 595 200 20" bgColOff="ff393939"
              textColOn="ffffffff" buttonText="Export Media" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stealthModeToggle" id="7779c3978e827c01" memberName="stealthModeToggle"
              virtualName="" explicitFocusOrder="0" pos="752 595 48 20" tooltip="This button activates &quot;Stealth Mode.&quot;  We may not always want to show the clients the notes we write about their performances, so when this button is engaged, Timestamped Notes and General Notes are hidden.  Additionally, it also deactivates the &quot;Insert Timestamp&quot; button."
              bgColOff="ff393939" bgColOn="ffffffff" textColOn="ff000000" buttonText=""
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="performersNameLabel" id="9c159bdc4788e13" memberName="performersNameLabel"
         virtualName="" explicitFocusOrder="0" pos="0 60 218 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Performer's Name:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial"
         fontsize="25.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="instrumentPlayedLabel" id="a34ed068d9f5ac5d" memberName="instrumentPlayedLabel"
         virtualName="" explicitFocusOrder="0" pos="0 95 218 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Instrument Played:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial"
         fontsize="25.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="microphonesUsedLabel" id="4e0c2b779c94a1e9" memberName="microphonesUsedLabel"
         virtualName="" explicitFocusOrder="0" pos="0 130 218 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Microphone(s) Used:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Arial"
         fontsize="25.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="performersNameEditor" id="81adb7f84cfa442" memberName="performersNameEditor"
              virtualName="" explicitFocusOrder="0" pos="218 60 282 30" bkgcol="ff565454"
              hilitecol="ff000000" outlinecol="ff565454" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="instrumentPlayedEditor" id="bfba21f7c37c1737" memberName="instrumentPlayedEditor"
              virtualName="" explicitFocusOrder="0" pos="218 95 282 30" bkgcol="ff565454"
              hilitecol="ff000000" outlinecol="ff565454" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="microphonesUsedEditor" id="f7810192bfd7721c" memberName="microphonesUsedEditor"
              virtualName="" explicitFocusOrder="0" pos="218 130 282 30" bkgcol="ff565454"
              hilitecol="ff000000" outlinecol="ff565454" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="timestampedNotesEditor" id="6efb7ce94469d9b7" memberName="timestampedNotesEditor"
              virtualName="" explicitFocusOrder="0" pos="0 200 500 175" bkgcol="ff565454"
              hilitecol="ff000000" outlinecol="ff565454" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="generalNotesEditor" id="fa606d1bbdb35fb6" memberName="generalNotesEditor"
              virtualName="" explicitFocusOrder="0" pos="0 415 1010 175" bkgcol="ff565454"
              hilitecol="ff000000" outlinecol="ff565454" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

