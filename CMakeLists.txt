cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# Explicitly instruct CMake to search the Geode CLI directory for build configs
list(APPEND CMAKE_MODULE_PATH "$ENV{USERPROFILE}/.geode/sdk/cmake")
list(APPEND CMAKE_PREFIX_PATH "$ENV{USERPROFILE}/.geode/sdk")

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
