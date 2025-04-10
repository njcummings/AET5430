/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GainEffectProcessor.h"

//==============================================================================
/**
*/
class Chorus_ReverbPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Chorus_ReverbPluginAudioProcessor();
    ~Chorus_ReverbPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static const bool BYPASSED_DEFAULT = false;
    
    bool isBypassed = BYPASSED_DEFAULT;
    
    static constexpr float GAIN_DEFAULT = 0.f;
    
    float gainValue = GAIN_DEFAULT;
    
    static constexpr float FREQ_DEFAULT = 1000.f;
    
    float freqValue = FREQ_DEFAULT;
    
private:
    
    GainEffectProcessor gain;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_ReverbPluginAudioProcessor)
};
