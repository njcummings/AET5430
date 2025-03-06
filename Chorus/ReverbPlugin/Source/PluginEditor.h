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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Chorus_ReverbPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_ReverbPluginAudioProcessorEditor)
};
