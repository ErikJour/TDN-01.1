/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TDN01AudioProcessor::TDN01AudioProcessor()
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
    apvts.state.addListener(this);
    castParameter(apvts, ParameterID::envAttack, envAttackParam);
    castParameter(apvts, ParameterID::envDecay, envDecayParam);
    castParameter(apvts, ParameterID::envSustain, envSustainParam);
    castParameter(apvts, ParameterID::envRelease, envReleaseParam);
    castParameter(apvts, ParameterID::noiseType, noiseTypeParam);
    castParameter(apvts, ParameterID::globalGain, globalGainParam);
    castParameter(apvts, ParameterID::lpCutoff, lpCutoffParam);
    castParameter(apvts, ParameterID::lpResonance, lpResonanceParam);
    castParameter(apvts, ParameterID::hpCutoff, hpCutoffParam);
    castParameter(apvts, ParameterID::lfoDepth, lfoDepthParam);
    castParameter(apvts, ParameterID::lfoRate, lfoRateParam);
    castParameter(apvts, ParameterID::lfoSource, lfoSourceParam);
    castParameter(apvts, ParameterID::lfoBSource, lfoBSourceParam);
    castParameter(apvts, ParameterID::lfoBDepth, lfoBDepthParam);
    castParameter(apvts, ParameterID::lfoBRate, lfoBRateParam);
}

TDN01AudioProcessor::~TDN01AudioProcessor()
{
    apvts.state.removeListener(this);

}

//==============================================================================
const juce::String TDN01AudioProcessor::getName() const
{
    juce::String pluginName {"TDN-01"};
    return JucePlugin_Name;
}

bool TDN01AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TDN01AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TDN01AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TDN01AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TDN01AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TDN01AudioProcessor::getCurrentProgram()
{
    return 0;
}

void TDN01AudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String TDN01AudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void TDN01AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);

}

//==============================================================================
void TDN01AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    noiseSynth.distributeResources(sampleRate, samplesPerBlock);
    parametersChanged.store(true);
    reset();
}

void TDN01AudioProcessor::releaseResources()
{
}

void TDN01AudioProcessor::reset()
{
    noiseSynth.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TDN01AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TDN01AudioProcessor::handleMidi(uint8_t data0, uint8_t data1, uint8_t data2)
{
    noiseSynth.midiMessages(data0, data1, data2);
}

void TDN01AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; i++)
        buffer.clear(i, 0, buffer.getNumSamples());
        
    bool expected = true;

    if (parametersChanged.compare_exchange_strong(expected, false))
    {
        update();
    }
    
    splitBufferByEvents(buffer, midiMessages);
    
    float envValue = noiseSynth.getEnvelopeValue();
    
    currentEnvelopeValue.store(envValue, std::memory_order_relaxed);
    
}

void TDN01AudioProcessor::render(juce::AudioBuffer<float>& buffer, int sampleCount, int bufferOffset)
{
    float* outputBuffers[2] = { nullptr, nullptr };
    
    outputBuffers[0] = buffer.getWritePointer(0) + bufferOffset;
    
    if (getTotalNumOutputChannels() > 1) {
        outputBuffers[1] = buffer.getWritePointer(1) + bufferOffset;
    }
    
    noiseSynth.render(outputBuffers, sampleCount);
}

void TDN01AudioProcessor::splitBufferByEvents(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    int bufferOffset = 0;
    
    for (const auto metadata : midiMessages) {
        
//        DBG("Received MIDI: " << (int)metadata.data[0]);
        
        int samplesThisSegment = metadata.samplePosition - bufferOffset;
        
        if (samplesThisSegment > 0) {
            
            render(buffer, samplesThisSegment, bufferOffset);
            
            bufferOffset += samplesThisSegment;
        }
        if (metadata.numBytes <= 3) {
            uint8_t data1 = (metadata.numBytes >= 2) ? metadata.data[1] : 0;
            uint8_t data2 = (metadata.numBytes == 3) ? metadata.data[2] : 0;
            handleMidi(metadata.data[0], data1, data2);
        }
    }
    
    int samplesLastSegment = buffer.getNumSamples() - bufferOffset;
    if (samplesLastSegment > 0) {
        render(buffer, samplesLastSegment, bufferOffset);
    }
    
    midiMessages.clear();
}

//==============================================================================
bool TDN01AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TDN01AudioProcessor::createEditor()
{
    return new TDN01AudioProcessorEditor (*this);
}

//==============================================================================
void TDN01AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
}

void TDN01AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data);
    juce::ignoreUnused(sizeInBytes);

}

juce::AudioProcessorValueTreeState::ParameterLayout
    TDN01AudioProcessor::createParameterLayout()

{
        juce::AudioProcessorValueTreeState::ParameterLayout layout;
        
        //Env Attack
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::envAttack,
        "Env Attack",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        20.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
        ));

        //Env Decay
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::envDecay,
        "Env Decay",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
        ));

        //Env Sustain
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::envSustain,
        "Env Sustain",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
        ));

        //Env Release
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::envRelease,
        "Env Release",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
        ));
        
        //Noise Type
        layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParameterID::noiseType,
        "Noise Type",
        juce::StringArray { "White", "Pink"},
        0));
        
        //Master Gain
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::globalGain,
        "Master Gain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.5f,
        juce::AudioParameterFloatAttributes().withLabel("Global Gain")
        ));
        
        //LP CUTOFF
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::lpCutoff,
        "Cutoff Freq",
        juce::NormalisableRange<float>(0.1f, 100.0f, 0.1f),
        80.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
        ));

        //Filter Rez
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::lpResonance,
        "Resonance",
        juce::NormalisableRange<float>(0.3f, 10.0f, 0.001f),
        2.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
        ));
        
        //HP Cutoff
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::hpCutoff,
        "High-pass Cutoff",
        juce::NormalisableRange<float>(0.1f, 75.0f, 0.01f),
        0.1f,
        juce::AudioParameterFloatAttributes().withLabel("%")
        ));

        //LFO Depth
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::lfoDepth,
        "LFO A Depth",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("Depth")
        ));

        //LFO Rate
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::lfoRate,
        "LFO A Rate",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("Depth")
        ));
        
        //LFO A Source
        layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParameterID::lfoSource,
        "LFO Source",
        juce::StringArray { "Volume", "LP Cutoff", "HP Cutoff"},
        0));
        
        //LFO B Source
        layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParameterID::lfoBSource,
        "LFO B Source",
        juce::StringArray { "Volume", "LP Cutoff", "HP Cutoff"},
        0));
        
        //LFO B Depth
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::lfoBDepth,
        "LFO B Depth",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("Depth")
        ));

        //LFO B Rate
        layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::lfoBRate,
        "LFO B Rate",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("Rate")
        ));
      
        return layout;
}

void TDN01AudioProcessor::update()
{
    float sampleRate = float(getSampleRate());
    float inverseSampleRate = 1.0f / sampleRate;

    //ADSR Controls
    noiseSynth.envAttack = std::exp(-inverseSampleRate * std::exp(5.5f - 0.075f * envAttackParam->get()));
    noiseSynth.envDecay = std::exp(-inverseSampleRate * std::exp(5.5f - 0.075f * envDecayParam->get()));
    noiseSynth.envSustain = envSustainParam->get() / 100.0f;
    float envRelease = envReleaseParam->get();

    if (envRelease < 1.0f)
      {
          noiseSynth.envRelease = 0.75f;
      }

    else{
          noiseSynth.envRelease = std::exp(-inverseSampleRate * std::exp(5.5f - 0.075f * envRelease));
      }

    float decayTime = envDecayParam->get() / 100.0f * 5.0f;
    float decaySamples = sampleRate * decayTime;
    noiseSynth.envDecay = std::exp(std::log(SILENCE) / decaySamples);
    
    //Noise Type Control
    int updatedNoiseType = noiseTypeParam->getIndex();
    noiseSynth.setNoiseType(updatedNoiseType);
    
    //Noise Level Update
    float globalGain = globalGainParam->get();
    globalGain *= globalGain;
    noiseSynth.setGain(globalGain);

    float filterCutoffFreq = lpCutoffParam->get();
    filterCutoffFreq *= filterCutoffFreq;
    float filterResoance = lpResonanceParam->get();
    filterResoance *= filterResoance;
    noiseSynth.updateLPFilterCoefficients(filterCutoffFreq, filterResoance);

   //High Pass Cutoff Update
    float highPassCutoff = hpCutoffParam->get();
    highPassCutoff *= highPassCutoff;
    noiseSynth.updateHPFilterCoefficients(highPassCutoff);

    //LFO Updates
    float lfoDepth = lfoDepthParam->get();
    lfoDepth *= lfoDepth;
    noiseSynth.updateLfoDepth(lfoDepth);

    float lfoRate = lfoRateParam->get();
    lfoRate *= lfoRate;
    noiseSynth.updateLfoRate(lfoRate);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TDN01AudioProcessor();
}
