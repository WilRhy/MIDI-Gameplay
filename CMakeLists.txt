cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# DYNAMIC PATH EXTRACTOR: Checks the cloud machine's temporary folders automatically
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_MODULE_PATH "$ENV{GEODE_SDK}/cmake")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
else()
    # Safe fallback mapping for local testing on your machine's C: drive
    list(APPEND CMAKE_MODULE_PATH "$ENV{USERPROFILE}/.geode/sdk/cmake")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{USERPROFILE}/.geode/sdk")
endif()

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
