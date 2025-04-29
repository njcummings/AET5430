/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

//==============================================================================
Chorus_ReverbPluginAudioProcessorEditor::Chorus_ReverbPluginAudioProcessorEditor (Chorus_ReverbPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // UI set up
    addAndMakeVisible(chorusLabel);
    chorusLabel.setText("Chorus", juce::dontSendNotification);
    chorusLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(reverbLabel);
    reverbLabel.setText("Reverb", juce::dontSendNotification);
    reverbLabel.setJustificationType(juce::Justification::centred);
    
    //Chorus sliders
    addAndMakeVisible(chorusRateSlider);
    chorusRateSlider.setSliderStyle(juce::Slider::Rotary);
    chorusRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(chorusDepthSlider);
    chorusDepthSlider.setSliderStyle(juce::Slider::Rotary);
    chorusDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(chorusDelaySlider);
    chorusDelaySlider.setSliderStyle(juce::Slider::Rotary);
    chorusDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(chorusFeedbackSlider);
    chorusFeedbackSlider.setSliderStyle(juce::Slider::Rotary);
    chorusFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(chorusMixSlider);
    chorusMixSlider.setSliderStyle(juce::Slider::Rotary);
    chorusMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    //Reverb sliders
    addAndMakeVisible(reverbRoomSizeSlider);
    reverbRoomSizeSlider.setSliderStyle(juce::Slider::Rotary);
    reverbRoomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(reverbDampingSlider);
    reverbDampingSlider.setSliderStyle(juce::Slider::Rotary);
    reverbDampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(reverbWidthSlider);
    reverbWidthSlider.setSliderStyle(juce::Slider::Rotary);
    reverbWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(reverbDryLevelSlider);
    reverbDryLevelSlider.setSliderStyle(juce::Slider::Rotary);
    reverbDryLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    addAndMakeVisible(reverbWetLevelSlider);
    reverbWetLevelSlider.setSliderStyle(juce::Slider::Rotary);
    reverbWetLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80,20);
    
    
    //Freeze button
    addAndMakeVisible(reverbFreezeButton);
    reverbFreezeButton.setButtonText("Freeze");
    
    //Attach control to parameters
    chorusRateAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"chorusRate", chorusRateSlider));
    chorusDepthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"chorusDepth", chorusDepthSlider));
    chorusDelayAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"chorusDelay", chorusDelaySlider));
    chorusFeedbackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"chorusFeedback", chorusFeedbackSlider));
    chorusMixAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"chorusMix", chorusMixSlider));
    
    reverbRoomSizeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"reverbRoomSize", reverbRoomSizeSlider));
    reverbDampingAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"reverbDamping", reverbDampingSlider));
    reverbWidthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"reverbWidth", reverbWidthSlider));
    reverbDryLevelAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"reverbDryLevel", reverbDryLevelSlider));
    reverbWetLevelAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(),"reverbWetLevel", reverbWetLevelSlider));
   
    
    setSize(600,400);
}

//==============================================================================
void Chorus_ReverbPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkcyan);
}
    
   

void Chorus_ReverbPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto chorusArea = area.removeFromLeft(area.getWidth()/2);
    auto reverbArea = area;
    
    //Position chorus controls
    
    chorusLabel.setBounds(chorusArea.removeFromTop(30));
    auto chorusSliderArea = chorusArea.reduced(10);
    auto chorusSliderWidth = chorusSliderArea.getWidth()/3;
    
    chorusRateSlider.setBounds(chorusSliderArea.removeFromLeft(chorusSliderWidth));
    chorusDepthSlider.setBounds(chorusSliderArea.removeFromLeft(chorusSliderWidth));
    chorusDelaySlider.setBounds(chorusSliderArea.removeFromLeft(chorusSliderWidth));
    chorusFeedbackSlider.setBounds(chorusSliderArea.removeFromLeft(chorusSliderWidth));
    chorusMixSlider.setBounds(chorusSliderArea.removeFromLeft(chorusSliderWidth));
    
    //Position reverb controls
    reverbLabel.setBounds(reverbArea.removeFromTop(30));
    auto reverbSliderArea = reverbArea.reduced(10);
    auto reverbSliderWidth = reverbSliderArea.getWidth()/3;
    
    reverbRoomSizeSlider.setBounds(reverbSliderArea.removeFromLeft(reverbSliderWidth));
    reverbDampingSlider.setBounds(reverbSliderArea.removeFromLeft(reverbSliderWidth));
    reverbRoomSizeSlider.setBounds(reverbSliderArea.removeFromLeft(reverbSliderWidth));
    reverbWidthSlider.setBounds(reverbSliderArea.removeFromLeft(reverbSliderWidth));
    reverbDryLevelSlider.setBounds(reverbSliderArea.removeFromLeft(reverbSliderWidth));
    reverbWetLevelSlider.setBounds(reverbSliderArea.removeFromLeft(reverbSliderWidth));

    reverbFreezeButton.setBounds(reverbArea.getX() + 10, reverbArea.getBottom() - 40,80,30);
}
