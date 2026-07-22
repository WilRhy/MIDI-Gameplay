#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <vector>

using namespace geode::prelude;

bool g_midiInitialized = false;

// Safe callback structure that won't confuse the compiler
void myMidiCallback(double deltatime, std::vector<unsigned char>* message, void* userData) {
    if (!message || message->empty()) return;

    unsigned char status = message->at(0);
    unsigned char type = status & 0xF0;

    if (type == 0x90 || type == 0x99) {
        unsigned char velocity = message->at(2);
        if (velocity > 0) {
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
