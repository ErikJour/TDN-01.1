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
    webNoiseTypeRelay{ParameterID::noiseType.getParamID()},
    webGlobalGainRelay{ParameterID::globalGain.getParamID()},
    webLPCutoffRelay{ParameterID::lpCutoff.getParamID()},
    webLPResonanceRelay{ParameterID::lpResonance.getParamID()},
    webHPCutoffRelay{ParameterID::hpCutoff.getParamID()},
    webViewGui{
        juce::WebBrowserComponent::Options{}
              .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
               .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}
               .withUserDataFolder(juce::File::getSpecialLocation(juce::File::tempDirectory)))
              .withResourceProvider([this](const auto& url){
              return getResource(url);},
              juce::URL{ juce::WebBrowserComponent::getResourceProviderRoot() }
                    .getOrigin())
              .withNativeIntegrationEnabled()
              .withUserScript(R"(console.log("C++ Backend here: This is run before any other loading happens.");)")
        .withOptionsFrom(webNoiseTypeRelay)
        .withOptionsFrom(webGlobalGainRelay)
        .withOptionsFrom(webLPCutoffRelay)
        .withOptionsFrom(webLPResonanceRelay)
        .withOptionsFrom(webHPCutoffRelay)
        },
        webNoiseTypeParameterAttachment{*p.apvts.getParameter(ParameterID::noiseType.getParamID()),
        webNoiseTypeRelay, nullptr},
        webGlobalGainParameterAttachment{*p.apvts.getParameter(ParameterID::globalGain.getParamID()),
        webGlobalGainRelay, nullptr},
        webLPCutoffParameterAttachment{*p.apvts.getParameter(ParameterID::lpCutoff.getParamID()),
        webLPCutoffRelay, nullptr},
        webLPResonanceParameterAttachment{*p.apvts.getParameter(ParameterID::lpResonance.getParamID()),
        webLPResonanceRelay, nullptr},
        webHPCutoffParameterAttachment{*p.apvts.getParameter(ParameterID::hpCutoff.getParamID()),
        webHPCutoffRelay, nullptr}
        
{
    addAndMakeVisible(webViewGui);
    juce::String localServer = "http://localhost:5173/";
    webViewGui.goToURL(localServer);
//    webViewGui.goToURL(webViewGui.getResourceProviderRoot());

    //PANELS
    topMenu = std::make_unique<TopPanel>(&audioProcessor);
    addAndMakeVisible(*topMenu);
    
    leftMenu = std::make_unique<LeftPanel>(&audioProcessor);
    addAndMakeVisible(*leftMenu);
    
    bottomMenu = std::make_unique<BottomPanel>(&audioProcessor);
    addAndMakeVisible(*bottomMenu);
    
    rightMenu = std::make_unique<RightPanel>(&audioProcessor);
    addAndMakeVisible(*rightMenu);
    
    setSize (PANEL_BASE_WIDTH, PANEL_BASE_HEIGHT);
    
    startTimer(30);
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
    
    //Panels
    bottomMenu->setBounds(0, 560, PANEL_BOTTOM_WIDTH, PANEL_BOTTOM_HEIGHT);
    leftMenu->setBounds(0, 0, PANEL_LEFT_WIDTH, PANEL_LEFT_HEIGHT);
    rightMenu->setBounds(PANEL_LEFT_WIDTH + PANEL_CENTER_WIDTH, PANEL_TOP_HEIGHT, PANEL_RIGHT_WIDTH, PANEL_RIGHT_HEIGHT);
    
}

void TDN01AudioProcessorEditor::timerCallback()
{
    envValue = audioProcessor.currentEnvelopeValue.load(std::memory_order_relaxed);
    sendEnvelopeValue(envValue);

}

void TDN01AudioProcessorEditor::sendEnvelopeValue(float newValue)
{
        static const juce::Identifier EVENT_ID("EnvelopeValue");
        webViewGui.emitEventIfBrowserIsVisible(EVENT_ID, newValue);
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
