if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "" FORCE)
endif()

if(APPLE)
    set(VST3_COPY_DIR "$ENV{HOME}/Library/Audio/Plug-Ins/VST3")
    set(AU_COPY_DIR "$ENV{HOME}/Library/Audio/Plug-Ins/Components")
elseif(WIN32)
    set(VST3_COPY_DIR "$ENV{COMMONPROGRAMFILES}/VST3")
endif()

juce_add_plugin(TDN01
        PLUGIN_NAME "TDN01"  # Add this line
        COMPANY_NAME AnimatedInstruments
        IS_SYNTH TRUE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        PLUGIN_MANUFACTURER_CODE JOUR
        PLUGIN_CODE TDN1
        FORMATS AU VST3 Standalone
        NEEDS_WEBVIEW2 TRUE
        COPY_PLUGIN_AFTER_BUILD TRUE
        VST3_COPY_DIR "${VST3_COPY_DIR}"
        AU_COPY_DIR "${AU_COPY_DIR}"
)

if(APPLE)
    set_target_properties(TDN01 PROPERTIES
            XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME "YES"
    )
endif()

target_sources(TDN01
        PRIVATE
        src/PluginEditor.cpp
        src/PluginProcessor.cpp
        src/dsp/Envelope.cpp
        src/dsp/EnvelopeListener.cpp
        src/dsp/Filter.cpp
        src/dsp/LFO.cpp
        src/dsp/noiseGenerator.cpp
        src/dsp/NoiseSynth.cpp
        src/dsp/PinkNoise.cpp
        src/window/BottomPanel.cpp
        src/window/CenterPanel.cpp
        src/window/LeftPanel.cpp
        src/window/MainMenuPanel.cpp
        src/window/OtherLookandFeel.cpp
        src/window/PanelBase.cpp
        src/window/RightPanel.cpp
        src/window/TDNComboBox.cpp
        src/window/TDNSlider.cpp
        src/window/TopPanel.cpp
)


target_include_directories(TDN01 PRIVATE include
        src
        UI
)

set(WEBVIEW_FILES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/UI/dist")

set(TARGET_WEBVIEW_FILES_ZIP_PATH "${CMAKE_BINARY_DIR}/webview_files.zip")

get_filename_component(PUBLIC_PATH "${WEBVIEW_FILES_SOURCE_DIR}" ABSOLUTE)

file(
        ARCHIVE_CREATE
        OUTPUT
        ${TARGET_WEBVIEW_FILES_ZIP_PATH}
        PATHS
        "${PUBLIC_PATH}"
        FORMAT
        zip
        VERBOSE
)

juce_add_binary_data(WebViewFiles
        HEADER_NAME WebViewFiles.h
        NAMESPACE webview_files
        SOURCES ${TARGET_WEBVIEW_FILES_ZIP_PATH}
)

target_link_libraries(TDN01
        PRIVATE
        WebViewFiles
        juce::juce_audio_utils
        juce::juce_gui_extra
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(TDN01
        PUBLIC
        JUCE_WEB_BROWSER=1
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
)

#WHEN YOU ADD THREE.JS---------------------
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../libs/juce/modules/juce_gui_extra/native/javascript"
        DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/UI/public/js/juce/"
)