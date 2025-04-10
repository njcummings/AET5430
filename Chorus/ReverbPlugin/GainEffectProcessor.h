//
//  GainEffectProcessor.h
//  ChorusReverbPlugin
//
//  Created by Nick Cummings on 4/9/25.
//

#pragma once

class GainEffectProcessor
{
public:
    
    void processBuffer(juce::AudioBuffer<float>& buffer, const int numChannels, const int numSamples){
        
        for (int = 0; c < numChannels; ++c){
            for (int n = 0; n< numSamples; ++n){
                float x = buffer.getWritePointer(c)[n];
                x = processSample(x);
                buffer.getWritePointer(c)[n] = x;
                
            }
        }
    }
    
    void process(float * buffer, const int numSamples){
        for (int n = 0; n < numSmaples; ++n){
            float x = buffer[n];
            x = processSample(x);
            buffer[n] = x;
        }
    }
    
    float processSample(float x){
        float y = x * linGain;
        return y;
    }
    void setGaindB(float dBGain){
        linGain = std::powf(10.f,dBGain/20.f);
        
    }
private:
    float linGain = 1.f;
};
