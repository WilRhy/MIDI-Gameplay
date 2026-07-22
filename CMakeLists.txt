cmake_minimum_required(VERSION 3.25)

project(MIDI-Gameplay VERSION 1.0.0)

# Progressive look-ahead routine to target the background folder trees dynamically
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cli-profile/geode/sdk/cmake")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cli-profile/geode/sdk/cmake")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cli-profile/geode/sdk")
else()
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cli-profile/geode/sdk/cmake")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cli-profile/geode/sdk")
endif()

find_package(Geode REQUIRED)

add_geode_mod(
    wilrhy.midi_gameplay
    VERSION 1.0.0
    RESOURCES about.md
    SOURCES
        src/main.cpp
)
