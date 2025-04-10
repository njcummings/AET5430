/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Chorus_ReverbPluginAudioProcessorEditor::Chorus_ReverbPluginAudioProcessorEditor (Chorus_ReverbPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    float scalar = 1.4f;
    int windowWidth = (int) (scalar * refWidth);
    int windowHeight = (int) (scalar * refHeight);
    setSize (windowWidth, windowHeight);
    
    int xPos = (int) ((20.f / refWidth) * windowWidth);
    int yPos = (int) ((30.f / refHeight) * windowHeight);
    int width = (int) ((150.f / refWidth) * windowWidth);
    int height = (int) ((20.f / refHeight) * windowHeight);
    
    bypassButton.addListener(this);
    bypassButton.setBounds(xPos,yPos,width,height); // x , y, width, height
    bypassButton.setButtonText("Bypass");
    bypassButton.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(bypassButton); // include this on the plugin window
    
    
    xPos = (int) ((200.f / refWidth) * windowWidth);
    yPos = (int) ((30.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = width; //(int) ((20.f / refHeight) * windowHeight);
    
    gainKnob.addListener(this);
    gainKnob.setBounds(xPos, yPos, width, height );
    gainKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnob.setRange(-48.f, 12.f, .1f);
    gainKnob.setValue(audioProcessor.GAIN_DEFAULT);
    gainKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(gainKnob);
    
    xPos = (int) ((20.f / refWidth) * windowWidth);
    yPos = (int) ((160.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = width; //(int) ((20.f / refHeight) * windowHeight);
    
    freqKnob.addListener(this);
    freqKnob.setBounds(xPos, yPos, width, height );
    freqKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqKnob.setRange(20.f, 20000.f, 1.f);
    freqKnob.setValue(audioProcessor.FREQ_DEFAULT);
    freqKnob.setSkewFactorFromMidPoint(1000.0);
    freqKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(freqKnob);
    
    xPos = (int) ((125.f / refWidth) * windowWidth);
    yPos = (int) ((160.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = width; //(int) ((20.f / refHeight) * windowHeight);
    
}

Chorus_ReverbPluginAudioProcessorEditor::~Chorus_ReverbPluginAudioProcessorEditor()
{
}

//==============================================================================
void Chorus_ReverbPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::green);

    
    auto bounds = getLocalBounds();
    
    float windowWidth = (float) bounds.getWidth();
    float windowHeight = (float) bounds.getHeight();
    
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f * windowHeight/refHeight));
    
    int xPos = (int) ((20.f / refWidth) * windowWidth);
    int yPos = (int) ((140.f / refHeight) * windowHeight);
    int width = (int) ((100.f / refWidth) * windowWidth);
    int height = (int) ((20.f / refHeight) * windowHeight);
    
    //g.drawFittedText ("My First Plugin", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("Freq", xPos,yPos,width,height, juce::Justification::centred, 1);
}

void Chorus_ReverbPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
void FirstPluginAudioProcessorEditor::buttonClicked (Button* button){
    
    if (button == &bypassButton){
        audioProcessor.isBypassed = button->getToggleState();
    }
}
void FirstPluginAudioProcessorEditor::sliderValueChanged (Slider * slider){
    
    if (slider == &gainKnob){
        audioProcessor.gainValue = slider->getValue();
    }
    
    if (slider == &freqKnob){
        audioProcessor.freqValue = slider->getValue();
    }
}
