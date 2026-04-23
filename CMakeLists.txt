cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(TDN01 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(ENV{WEBVIEW2_DEFAULT_BACKGROUND_COLOR} "FF000000")

add_subdirectory(libs/juce)

add_subdirectory(plugin)
