/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

namespace {
auto streamToVector (juce::InputStream& stream) {
    using namespace juce;

    std::vector<std::byte> result ((size_t) stream.getTotalLength());
    stream.setPosition (0);
    [[maybe_unused]] const auto bytesRead = stream.read (result.data(), result.size());
    jassert (bytesRead == (ssize_t) result.size());
    return result;
}

const char* getMimeForExtension (const juce::String& extension)
{
    using namespace juce;
    static const std::unordered_map<String, const char*> mimeMap =
    {
        { { "htm"   },  "text/html"                },
        { { "html"  },  "text/html"                },
        { { "txt"   },  "text/plain"               },
        { { "jpg"   },  "image/jpeg"               },
        { { "jpeg"  },  "image/jpeg"               },
        { { "svg"   },  "image/svg+xml"            },
        { { "ico"   },  "image/vnd.microsoft.icon" },
        { { "json"  },  "application/json"         },
        { { "png"   },  "image/png"                },
        { { "css"   },  "text/css"                 },
        { { "map"   },  "application/json"         },
        { { "js"    },  "text/javascript"          },
        { { "woff2" },  "font/woff2"               }
    };

    if (const auto it = mimeMap.find (extension.toLowerCase()); it != mimeMap.end())
        return it->second;

    jassertfalse;
    return "";
}
}

//==============================================================================
TDN01AudioProcessorEditor::TDN01AudioProcessorEditor (TDN01AudioProcessor& p)
    : AudioProcessorEditor (&p), 
    audioProcessor (p),
    webNoiseTypeRelay{webViewGui, ParameterID::noiseType.getParamID()},
    webGlobalGainRelay{webViewGui, ParameterID::masterGain.getParamID()},
//    webNoiseTypeRelay{ParameterID::noiseType.getParamID()},
    webViewGui{
        juce::WebBrowserComponent::Options{}
              .withBackend(juce::WebBrowserComponent::Options::Backend::defaultBackend)
              .withResourceProvider([this](const auto& url){
              return getResource(url);},
              juce::URL{ juce::WebBrowserComponent::getResourceProviderRoot() }
                    .getOrigin())
              .withNativeIntegrationEnabled()
              .withUserScript(R"(console.log("C++ Backend here: This is run before any other loading happens.");)")
        .withOptionsFrom(webNoiseTypeRelay)
        .withOptionsFrom(webGlobalGainRelay)
        },
        webNoiseTypeParameterAttachment{*p.apvts.getParameter(ParameterID::noiseType.getParamID()),
        webNoiseTypeRelay, nullptr},
        webGlobalGainParameterAttachment{*p.apvts.getParameter(ParameterID::masterGain.getParamID()),
        webGlobalGainRelay, nullptr}
        
{
    addAndMakeVisible(webViewGui);
    juce::String localServer = "http://localhost:5173/";
    webViewGui.goToURL(localServer);
//    webViewGui.goToURL(webViewGui.getResourceProviderRoot());
    
    //AMP ENV ATTACK
    ampEnvAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampEnvAttackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(ampEnvAttackSlider);
    
    //AMP ENV DECAY
    ampEnvDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampEnvDecaySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(ampEnvDecaySlider);
    
    //AMP ENV SUSTAIN
    ampEnvSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampEnvSustainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(ampEnvSustainSlider);
    
    //AMP ENV RELEASE
    ampEnvReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampEnvReleaseSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(ampEnvReleaseSlider);
    
    //MASTER GAIN
    masterGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    masterGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(masterGainSlider);
    
    //LABELS========================================================================================
    
    //NAME LABEL
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
//    nameLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    nameLabel.setEditable (true);
    nameLabel.setText ("TDN-01", juce::dontSendNotification);
    addAndMakeVisible(nameLabel);
    
    //ENV LABEL
    envLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    envLabel.setText ("Amp Env", juce::dontSendNotification);
    envLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(envLabel);
    
    //FILTER LABEL
    filterLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    filterLabel.setText ("Filter", juce::dontSendNotification);
    filterLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterLabel);
    
    //Global GAIN LABEL
    globalGainLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    globalGainLabel.setText ("Global Gain", juce::dontSendNotification);
    globalGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(globalGainLabel);
    
    
    setSize (1000, 660);
}

TDN01AudioProcessorEditor::~TDN01AudioProcessorEditor()
{
}

//==============================================================================


void TDN01AudioProcessorEditor::resized()
{
    int webViewWidth = 700;
    int webViewHeight = 530;
    
    //WEBVIEW
    webViewGui.setBounds(100, 30, webViewWidth, webViewHeight);
    
    //SLIDERS
    ampEnvAttackSlider.setBounds(820, 60, 80, 80);
    ampEnvDecaySlider.setBounds(900, 60, 80, 80);
    ampEnvSustainSlider.setBounds(820, 140, 80, 80);
    ampEnvReleaseSlider.setBounds(900, 140, 80, 80);
    masterGainSlider.setBounds(20, 570, 60, 60);
    
    //LABELS
    nameLabel.setBounds(22, 0, 100, 50);
    envLabel.setBounds(850, 10, 100, 50);
    filterLabel.setBounds(850, 220, 100, 50);
    globalGainLabel.setBounds(2.5, 540, 100, 50);
}

auto TDN01AudioProcessorEditor::getResource(const juce::String& url) -> std::optional<Resource>
{
    
    std::cout << url << std::endl;
    
    static const auto resourceFileRoot = juce::File{R"(/Users/ejourgensen/Projects/TDN-01/UI)"};
    
    const auto resourceToRetrieve =url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);
    
    const auto resource = resourceFileRoot.getChildFile(resourceToRetrieve).createInputStream();
    
    if (resource) {
        
        const auto extension = resourceToRetrieve.fromLastOccurrenceOf(".", false, false);
        return Resource{streamToVector(*resource), getMimeForExtension(extension)};
    }
    
    return std::nullopt;
}
