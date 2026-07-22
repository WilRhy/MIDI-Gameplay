cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# Clean, cross-platform home directory configuration parsing
if(DEFINED ENV{USERPROFILE})
    set(GEODE_HOME_DIR "$ENV{USERPROFILE}")
else()
    set(GEODE_HOME_DIR "$ENV{HOME}")
endif()

# Bind directly to the absolute Geode CLI paths using the clean folder parsing
list(APPEND CMAKE_MODULE_PATH "${GEODE_HOME_DIR}/.geode/sdk/cmake")
list(APPEND CMAKE_PREFIX_PATH "${GEODE_HOME_DIR}/.geode/sdk")

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
