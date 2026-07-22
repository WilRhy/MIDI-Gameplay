#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include <iostream>
#include <vector>

using namespace geode::prelude;

bool g_midiInitialized = false;

// The callback that receives signals directly from your hardware items
void myMidiCallback(double deltatime, std::vector<unsigned char>* message, void* userData) {
    if (!message || message->empty()) return;

    unsigned char status = message->at(0);
    unsigned char type = status & 0xF0;

    // 0x90 = Piano Key / Pad Strike (Note On)
    // 0x99 = Some drum kits or specific launchpads use channel 10 exclusively
    if (type == 0x90 || type == 0x99) {
        unsigned char note = message->at(1);     // Key or Pad signature ID
        unsigned char velocity = message->at(2); // How hard it was struck

        // Ensure it's a real hit, not a release (velocity > 0)
        if (velocity > 0) {
            log::info("MIDI Trigger Detected! Note ID: {}, Velocity: {}", (int)note, (int)velocity);

            // Execute on the main thread loop safely
            Loader::get()->queueInMainThread([]() {
                // Dynamically invoke the keybind action we declared in mod.json
                auto actionHandler = ActionBindingHandler::get();
                if (actionHandler) {
                    actionHandler->triggerAction("your_name.midi_gameplay/midi_jump");
                }
            });
        }
    }
}

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontRunActions) {
        if (!PlayLayer::init(level, useReplay, dontRunActions)) {
            return false;
        }

        if (!g_midiInitialized) {
            log::info("Connecting custom keybind pipeline to MIDI controller...");
            
            // Your production build pipeline will open the hardware client hook here:
            // rtmidiIn->setCallback(&myMidiCallback, this);
            // rtmidiIn->openPort(0);
            
            g_midiInitialized = true;
        }

        return true;
    }

    void onExit() {
        PlayLayer::onExit();
        g_midiInitialized = false;
    }
};
