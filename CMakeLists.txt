cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# Clean, safe environmental mapping that drops the buggy formatting line completely
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_MODULE_PATH "$ENV{GEODE_SDK}/cmake")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
