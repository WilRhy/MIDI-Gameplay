#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <vector>
#include <string>

using namespace geode::prelude;

bool g_midiInitialized = false;

void myMidiCallback(double deltatime, std::vector<unsigned char>* message, void* userData) {
    if (!message || message->empty()) return;

    unsigned char status = message->at(0);
    unsigned char velocity = message->at(2);

    std::string currentMode = Mod::get()->getSettingValue<std::string>("input-mode");

    if (velocity > 0) {
        bool shouldTriggerJump = false;

        if (currentMode == "drum_pad" && status == 0x99) {
            shouldTriggerJump = true;
        } 
        else if (currentMode == "piano_key" && status == 0x90) {
            shouldTriggerJump = true;
        }

        if (shouldTriggerJump) {
            log::info("Validated MIDI Input Event! Firing custom action trigger...");
            Loader::get()->queueInMainThread([]() {
                auto actionHandler = ActionBindingHandler::get();
                if (actionHandler) {
                    actionHandler->triggerAction("wilrhy.midi_gameplay/midi_jump");
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
            log::info("MIDI keybind pipeline hooked successfully.");
            g_midiInitialized = true;
        }

        return true;
    }

    void onExit() {
        PlayLayer::onExit();
        g_midiInitialized = false;
    }
};
