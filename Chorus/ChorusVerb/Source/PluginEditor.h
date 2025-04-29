/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Chorus_ReverbPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Chorus_ReverbPluginAudioProcessorEditor (Chorus_ReverbPluginAudioProcessor&);
    ~Chorus_ReverbPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Chorus_ReverbPluginAudioProcessor&audioProcessor;
    
    //Chorus controls
    
    juce::Slider chorusRateSlider;
    juce::Slider chorusDepthSlider;
    juce::Slider chorusDelaySlider;
    juce::Slider chorusFeedbackSlider;
    juce::Slider chorusMixSlider;
    
    //Reverb controls
    
    juce::Slider reverbRoomSizeSlider;
    juce::Slider reverbDampingSlider;
    juce::Slider reverbWetLevelSlider;
    juce::Slider reverbDryLevelSlider;
    juce::Slider reverbWidthSlider;
    juce::ToggleButton reverbFreezeButton;
    
    //labels
    
    juce::Label chorusLabel;
    juce::Label reverbLabel;
    
    // Attachments
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusRateAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusDepthAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusDelayAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusFeedbackAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusMixAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbRoomSizeAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbDampingAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbWetLevelAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbDryLevelAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbWidthAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbFreezeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_ReverbPluginAudioProcessorEditor)
};
