cmake_minimum_required(VERSION 3.25)

# Initialize the MIDI Gameplay Mod project
project(MIDI-Gameplay VERSION 1.0.0)

# Tell CMake to find the Geode package automatically via the action toolchain
find_package(Geode REQUIRED)

# Package your C++ source file using your developer profile ID
add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
