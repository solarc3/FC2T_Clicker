#include <thread>
#include <iostream>
#include "clicker.h"
#include "imgui.h"
#include <windows.h>

void clicker::backgroundTask(unsigned int &keyHexValue) {
    while (true) {  // Add a loop to continuously check the key state
        if ((GetAsyncKeyState(keyHexValue) & 0x8000) != 0) {
            std::cout << "Key with hex value " << std::hex << keyHexValue << " is down." << std::endl;
        } else {
            std::cout << "Key with hex value " << std::hex << keyHexValue << " is not down." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Add a delay to reduce CPU usage
    }
}

void clicker::startBackgroundTask(unsigned int &keyHexValue) {
    std::jthread bgThread([&keyHexValue]() { backgroundTask(keyHexValue); });
    bgThread.detach();
}


void clicker::KeySelectionCombo(const char *combo_label, unsigned int &selectedKey) {
    std::string currentKeyString = "Select a key";
    for (const auto &key: clicker::keyMap) {
        if (key.second == selectedKey) {
            currentKeyString = key.first;
            break;
        }
    }
    ImGui::PushItemWidth(150);
    if (ImGui::BeginCombo(combo_label, currentKeyString.c_str())) {
        for (const auto &key: clicker::keyMap) {
            bool is_selected = (selectedKey == key.second);
            if (ImGui::Selectable(key.first.c_str(), is_selected)) {
                selectedKey = key.second;
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}
