#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Hook into the main menu layer to verify the mod is injected
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        // Run the original game code first
        if (!MenuLayer::init()) {
            return false;
        }

        // Print a message to the developer console log
        log::info("MIDI-Gameplay mod initialized successfully!");
        
        return true;
    }
};
