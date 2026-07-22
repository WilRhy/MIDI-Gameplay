cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# Check all possible locations where the build action saves FindGeode.cmake
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_MODULE_PATH "$ENV{GEODE_SDK}/cmake")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/geode-sdk/cmake")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/geode-sdk/cmake")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/geode-sdk")
elseif(DEFINED ENV{USERPROFILE})
    list(APPEND CMAKE_MODULE_PATH "$ENV{USERPROFILE}/.geode/sdk/cmake")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{USERPROFILE}/.geode/sdk")
else()
    list(APPEND CMAKE_MODULE_PATH "$ENV{HOME}/.geode/sdk/cmake")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/.geode/sdk")
endif()

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
