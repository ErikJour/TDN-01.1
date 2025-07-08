/*
  ==============================================================================

    NoiseSynth.cpp
    Created: 30 Jun 2025 9:05:10pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "NoiseSynth.h"

NoiseSynth::NoiseSynth()
{
    sampleRate = 44100.0;
    voice.lfo.setRate(0.4f);
    voice.lfo.setDepth(0.5f);

}

void NoiseSynth::distributeResources(double sampleRate, int samplesPerBlock)
{
    sampleRate = this->sampleRate;
    voice.lfo.setSampleRate(sampleRate);
}

void NoiseSynth::releaseResources()
{
    
}

void NoiseSynth::reset()
{
    voice.reset();
}

void NoiseSynth::render(float** outputBuffers, int sampleCount)
{
    float* outputBufferLeft = outputBuffers[0];
    float* outputBufferRight = outputBuffers[1];
    
    for (int sample = 0; sample < sampleCount; sample++) {
        
        float output = voice.render();
        
        outputBufferLeft[sample] = output;
                
        if (outputBufferRight != nullptr) {
            
            outputBufferRight[sample] = output;
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

