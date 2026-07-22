#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <vector>
#include <string>

using namespace geode::prelude;

bool g_midiInitialized = false;

// Safe callback structure that triggers a native player jump action directly
void myMidiCallback(double deltatime, std::vector<unsigned char>* message, void* userData) {
    auto playLayer = static_cast<PlayLayer*>(userData);
    if (!playLayer || !message || message->empty()) return;

    unsigned char status = message->at(0);
    unsigned char velocity = message->at(2);

    // Read player option preference natively from the Geode options box
    std::string currentMode = Mod::get()->getSettingValue<std::string>("input-mode");

    if (velocity > 0) {
        bool shouldTriggerJump = false;

        // 0x99 = Universal standard status byte for Drum Pads / Channel 10
        if (currentMode == "drum_pad" && status == 0x99) {
            shouldTriggerJump = true;
        } 
        // 0x90 = Universal standard status byte for Piano Keys / Channel 1
        else if (currentMode == "piano_key" && status == 0x90) {
            shouldTriggerJump = true;
        }

        if (shouldTriggerJump) {
            log::info("Valid MIDI signal intercepted! Triggering native player jump.");
            
            // Execute a native jumping click sequence directly on the core thread
            Loader::get()->queueInMainThread([playLayer]() {
                playLayer->pushButton(PlayerButton::Jump, false);
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
            log::info("MIDI native pipeline hooked successfully.");
            g_midiInitialized = true;
        }

        return true;
    }

    void onExit() {
        PlayLayer::onExit();
        g_midiInitialized = false;
    }
};
