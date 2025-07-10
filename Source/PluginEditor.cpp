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
        },
        webNoiseTypeParameterAttachment{*p.apvts.getParameter(ParameterID::noiseType.getParamID()),
        webNoiseTypeRelay, nullptr}
        
{
    addAndMakeVisible(webViewGui);
    juce::String localServer = "http://localhost:5173/";
    webViewGui.goToURL(localServer);
//    webViewGui.goToURL(webViewGui.getResourceProviderRoot());
    
    ampEnvAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setSize (800, 600);
}

TDN01AudioProcessorEditor::~TDN01AudioProcessorEditor()
{
}

//==============================================================================


void TDN01AudioProcessorEditor::resized()
{
    webViewGui.setBounds(getLocalBounds());
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
