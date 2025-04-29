/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Chorus_ReverbPluginAudioProcessor::Chorus_ReverbPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Chorus_ReverbPluginAudioProcessor::~Chorus_ReverbPluginAudioProcessor()
{
}

//==============================================================================
const juce::String Chorus_ReverbPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Chorus_ReverbPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Chorus_ReverbPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Chorus_ReverbPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Chorus_ReverbPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Chorus_ReverbPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Chorus_ReverbPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Chorus_ReverbPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Chorus_ReverbPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Chorus_ReverbPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Chorus_ReverbPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //Prepare chorus
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    chorus.prepare(spec);
    chorus.setRate(chorusRate);
    chorus.setDepth(chorusDepth);
    chorus.setCentreDelay(chorusDelay);
    chorus.setFeedback(chorusFeedback);
    chorus.setMix(chorusMix);
    
    //Prepare reverb
    reverb.prepare(spec);
    
    //Update reverb parameters
    reverbParams.roomSize = reverbRoomSize;
    reverbParams.damping = reverbDamping;
    reverbParams.wetLevel = reverbWetLevel;
    reverbParams.dryLevel = reverbDryLevel;
    reverbParams.width = reverbWidth;
    reverbParams.freezeMode = reverbFreezeMode;
    
    reverb.setParameters(reverbParams);
    
    //Prepare temp buffer
    tempBuffer.setSize(getTotalNumOutputChannels(), samplesPerBlock);
}

void Chorus_ReverbPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Chorus_ReverbPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void Chorus_ReverbPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
   
   // Apply chorus
    juce::dsp::AudioBlock<float> block(buffer);
    
    juce::dsp::ProcessContextReplacing<float> context(block);
    chorus.process(context);
    
    //Apply reverb
    reverb.process(context);
}

void Chorus_ReverbPluginAudioProcessor::createParameters()
{
    apvts.reset(new juce::AudioProcessorValueTreeState(*this, nullptr, "Parameters", createParameterLayout()));
}
juce::AudioProcessorValueTreeState::ParameterLayout Chorus_ReverbPluginAudioProcessor::createParameterLayout(){
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    //Chorus parameters
    layout.add(std::make_unique<juce::AudioParameterFloat>("chorusRate","Chorus Rate", juce::NormalisableRange<float>(0.1f,5.0f,0.01f,0.5f),1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("chorusDepth","Chorus Depth", juce::NormalisableRange<float>(0.0f,1.0f,0.01f),0.25f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("chorusDelay","Chorus Delay", juce::NormalisableRange<float>(1.0f,20.0f,0.01f),7.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("chorusFeedback","Chorus Feedback", juce::NormalisableRange<float>(-1.0f,1.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("chorusMix","Chorus Mix", juce::NormalisableRange<float>(0.0f,1.0f,0.01f),0.5f));
    
    //reverb parameters
    layout.add(std::make_unique<juce::AudioParameterFloat>("reverbRoomSize","Room Size", juce::NormalisableRange<float>(0.0f,1.0f,0.01f),0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("reverbDamping","Damping", juce::NormalisableRange<float>(0.0f,1.0f,0.01f),0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("reverbDryLevel","Dry Level", juce::NormalisableRange<float>(0.0f,1.0f,0.01f),0.4f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("reverbWetLevel","Wet Level", juce::NormalisableRange<float>(0.0f,1.0f,0.01f),0.33f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("reverbWidth","Width", juce::NormalisableRange<float>(0.0f,1.0f,0.01f),1.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>("reverbFreeze","Freeze Mode", false));
    
    return layout;
}
//==============================================================================
bool Chorus_ReverbPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Chorus_ReverbPluginAudioProcessor::createEditor()
{
    return new Chorus_ReverbPluginAudioProcessorEditor (*this);
}

//==============================================================================
void Chorus_ReverbPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Chorus_ReverbPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Chorus_ReverbPluginAudioProcessor();
}
