cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# Intercept and convert the runner's path variable into a clean string layout
if(DEFINED ENV{GEODE_SDK})
    cmake_path(SET REAL_SDK_PATH CONVERT "ENV{GEODE_SDK}" TO_CMAKE_PATH_LIST)
    list(APPEND CMAKE_MODULE_PATH "${REAL_SDK_PATH}/cmake")
    list(APPEND CMAKE_PREFIX_PATH "${REAL_SDK_PATH}")
endif()

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
