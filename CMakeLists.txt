cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# Explicitly direct CMake to the exact folder where the runner drops the SDK
list(APPEND CMAKE_MODULE_PATH "D:/a/MIDI-Gameplay/MIDI-Gameplay/cli-profile/geode/sdk/cmake")
list(APPEND CMAKE_PREFIX_PATH "D:/a/MIDI-Gameplay/MIDI-Gameplay/cli-profile/geode/sdk")

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
