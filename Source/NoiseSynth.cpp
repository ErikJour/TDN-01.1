/*
  ==============================================================================

    NoiseSynth.cpp
    Created: 30 Jun 2025 9:05:10pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "NoiseSynth.h"

NoiseSynth::NoiseSynth() : envAttack(0.0f), envDecay(0.0f), envSustain(0.0f), envRelease(0.0f)
{
    sampleRate = 44100.0;
    voice.lfo.setRate(0.4f);
    voice.lfo.setDepth(0.5f);
    gainSmoothed.reset(sampleRate, 0.01f);

}

void NoiseSynth::distributeResources(double sampleRate_, int samplesPerBlock)
{
    sampleRate = static_cast<float> (sampleRate_);
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlock), 1 };

    //LFO SETUP
    voice.lfo.setSampleRate(sampleRate);

    //Low Pass Filter Setup
    voice.lowPassFilter.setMode(juce::dsp::LadderFilterMode::LPF12);
    voice.lowPassFilter.prepare(spec);

    //High Pass Filter Setup
    voice.highPassFilter.setMode(juce::dsp::LadderFilterMode::HPF24);
    voice.highPassFilter.prepare(spec);

}

void NoiseSynth::releaseResources()
{
    
}

void NoiseSynth::reset()
{
    voice.reset();
    gainSmoothed.reset(sampleRate, 0.01f);
}

void NoiseSynth::render(float** outputBuffers, int sampleCount)
{
    float* outputBufferLeft = outputBuffers[0];
    float* outputBufferRight = outputBuffers[1];
    
    for (int sample = 0; sample < sampleCount; sample++) {
        
        float output = voice.render();
        
        float gain = gainSmoothed.getNextValue();
        
        outputBufferLeft[sample] = output * gain;
    
                
        if (outputBufferRight != nullptr) {
            
            outputBufferRight[sample] = output * gain;
        }
        
        if (!voice.env.isActive()) {
            voice.env.reset();
        }
    }
    
    
    protectMyEars(outputBufferLeft, sampleCount);
    protectMyEars(outputBufferRight, sampleCount);
    
    
}

void NoiseSynth::midiMessages(uint8_t data0, uint8_t data1, uint8_t data2)
{
    switch (data0 & 0xF0){
        case 0x80:
            noteOff(data1 & 0x7f);
            break;
        case 0x90:
            uint8_t note = data1 & 0x7F;
            uint8_t velocity = data2 & 0x7F;
            if (velocity > 0) {
                noteOn(note, velocity);
            }
            else {
                noteOff(note);
            }
            break;
    }
}

void NoiseSynth::startVoice(int note, int velocity)
{
    voice.note = note;
    voice.noise.setAmplitude(velocity / 127.0f);
    
    Envelope& env = voice.env;
    env.attackMultiplier = envAttack;
    env.decayMultiplier = envDecay;
    env.sustainLevel = envSustain;
    env.releaseMultiplier = envRelease;
    env.attack();
    
}
void NoiseSynth::noteOn(int note, int velocity)
{
    startVoice(note, velocity);
    
}
void NoiseSynth::noteOff(int note)
{
    if (voice.note == note) {
        voice.note = 0;
    }
    
}

void NoiseSynth::setNoiseType(int newNoiseType)
{
    voice.noiseType = newNoiseType;
}

void NoiseSynth::setGain (float newGain)
{
    gainSmoothed.setTargetValue(newGain);
}

float NoiseSynth::getEnvelopeValue()
{
    return voice.env.nextValue();
}

void NoiseSynth::updateLPFilterCoefficients(float cutoff, float resonance)
{
   
        voice.updateLPFilter(cutoff, resonance); 
    
}

void NoiseSynth::updateHPFilterCoefficients(float cutoff)
{
    voice.updateHPFilter(cutoff);
}


