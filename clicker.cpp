#include <thread>
#include <iostream>
#include "clicker.h"
#include "imgui.h"
#include "jitter.h"
#include <windows.h>

void clicker::LeftBackgroundTask(unsigned int &keyHexValue, bool &clickerStatus, int &current, bool &LeftJitter) {
    static bool toggleState = false;
    static bool wasDown = false;
    while (true) {
        if (clickerStatus) {
            bool isKeyDown = (GetAsyncKeyState(keyHexValue) & 0x8000) != 0;
            switch (current) {
                case 1: // Toggle
                    if (isKeyDown && !wasDown) {
                        toggleState = !toggleState;
                        wasDown = true;
                    } else if (!isKeyDown && wasDown) {
                        wasDown = false;
                    }
                    if (toggleState && LeftJitter) {
                            std::cout << " TOGGLE ON AND Jitter Active"<< std::endl;
                    } else {
                        if(toggleState){
                            std::cout << " TOGGLE ON"<< std::endl;
                        }
                        else{
                            std::cout << " TOGGLE OFF"<< std::endl;
                        }
                    }
                    break;
                case 0: // Hold
                    if (LeftJitter && isKeyDown) {
                        std::cout << "Hold ON with Jitter: Key with hex value " << std::hex << keyHexValue << std::endl;
                    } else {
                        if (isKeyDown) {
                            std::cout << "Hold ON: Key with hex value " << std::hex << keyHexValue << std::endl;
                        } else {
                            std::cout << "Hold OFF: Key with hex value " << std::hex << keyHexValue << std::endl;
                        }
                    }
                    break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}


void clicker::startBackgroundTask(unsigned int &keyHexValue) {
    std::jthread bgThread([&keyHexValue]() {LeftBackgroundTask(keyHexValue, clicker::LeftClickerStatus, clicker::current, jitter::LeftJitter);});
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
