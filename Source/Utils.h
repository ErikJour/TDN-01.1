/*
  ==============================================================================

    Utils.h
    Created: 30 Jun 2025 9:21:45pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

inline void protectMyEars(float* buffer, int sampleCount)
{
    if (buffer == nullptr)
    {
        return;
    }
    bool firstWarning = true;
    for (int i = 0; i < sampleCount; i++)
    {
        float x = buffer[i];
        bool silence = false;
        if (std::isnan(x))
        {
            DBG("!!! WARNING: Silencing NOW");
            silence = true;
        }
        else if (std::isinf(x))
        {
             DBG("!!! WARNING: Silencing NOW");
            silence = true;
        }
        else if (x < -2.0f || x > 2.0f)
        {
             DBG("!!! WARNING: Sample out of Range, silencing!");
            silence = true;
        }
          else if (x < -1.0f)
        {
             if (firstWarning)
             {
                DBG("!!! sample out of range, clamping !!!");
                firstWarning = false;
             }
             buffer[i] = -1.0f;
        }
          else if (x > 1.0f)
        {
             if (firstWarning)
             {
                DBG("!!! sample out of range, clamping !!!");
                firstWarning = false;
             }
             buffer[i] = 1.0f;
        }
        if (silence)
        {
            memset(buffer, 0, static_cast<size_t>(sampleCount) * sizeof(float));
            return;
        }

    }
}

template<typename T>
inline static void castParameter(juce::AudioProcessorValueTreeState& apvts,
                                const juce::ParameterID& id, T& destination)
                                {
                                    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
                                    jassert(destination);
                                }
