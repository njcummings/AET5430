/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_audio_processors/juce_audio_processors.h>


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

    juce::AudioProcessorValueTreeState&getAPVTS() {return *apvts;}
    
    private:
    //Chorus Parameters
    juce::dsp::Chorus<float> chorus;
    float chorusRate = 1.0f;
    float chorusDepth = 0.25f;
    float chorusDelay = 7.0f;
    float chorusFeedback = 0.0f;
    float chorusMix = 0.5f;
    
    //Reverb Parameters
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams;
    float reverbRoomSize = 0.5f;
    float reverbDamping = 0.5f;
    float reverbWetLevel = 0.33f;
    float reverbDryLevel = 0.4f;
    float reverbWidth = 1.0f;
    float reverbFreezeMode = 0.0f;
    
    //Audio Buffer
    juce::AudioBuffer<float> tempBuffer;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState> apvts;
    
    void createParameters();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_ReverbPluginAudioProcessor)
};
