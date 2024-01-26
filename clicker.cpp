#include <thread>
#include <iostream>
#include "clicker.h"
#include "imgui.h"
#include "jitter.h"
#include <windows.h>
#include <random>
#include <chrono>
#include <math.h>


void clicker::BackgroundTask(unsigned int &keyHexValue, bool &clickerStatus, int &current, bool &Jitter, int mouse_code) {
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
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
                    if (toggleState && Jitter) {
                        clicker::sendclick((mouse_code == 1) ? clicker::LeftTargetedCPS : clicker::RightTargetedCPS,
                                           (mouse_code == 1) ? FC2_TEAM_MOUSE_CODE::FC2_TEAM_MOUSE_LEFT : FC2_TEAM_MOUSE_CODE::FC2_TEAM_MOUSE_RIGHT);
                    }
                    else {
                        if(toggleState){
                            clicker::sendclick((mouse_code == 1) ? clicker::LeftTargetedCPS : clicker::RightTargetedCPS,
                                               (mouse_code == 1) ? FC2_TEAM_MOUSE_CODE::FC2_TEAM_MOUSE_LEFT : FC2_TEAM_MOUSE_CODE::FC2_TEAM_MOUSE_RIGHT);
                        }
                        break;
                    }
                break;
                case 0: // Hold
                    if (Jitter && isKeyDown) {
                        clicker::sendclick((mouse_code == 1) ? clicker::LeftTargetedCPS : clicker::RightTargetedCPS,
                                           (mouse_code == 1) ? FC2_TEAM_MOUSE_LEFT : FC2_TEAM_MOUSE_RIGHT);
                    } else {
                        if (isKeyDown) {
                            clicker::sendclick((mouse_code == 1) ? clicker::LeftTargetedCPS : clicker::RightTargetedCPS,
                                               (mouse_code == 1) ? FC2_TEAM_MOUSE_LEFT : FC2_TEAM_MOUSE_RIGHT);
                        }
                        break;
                    }
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}


void clicker::LeftBackgroundTask(unsigned int &keyHexValue, int code) {
    std::jthread bgThread([&keyHexValue, code]() {BackgroundTask(keyHexValue, clicker::LeftClickerStatus, clicker::current, jitter::LeftJitter, code);});
    bgThread.detach();
}
void clicker::RightBackgroundTask(unsigned int &keyHexValue, int code) {
    std::jthread bgThread([&keyHexValue, code]() {BackgroundTask(keyHexValue, clicker::RightClickerStatus, clicker::current, jitter::RightJitter, code);});
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
//https://blat-blatnik.github.io/computerBear/making-accurate-sleep-function/
void timerSleep(double seconds) {
    using namespace std::chrono;

    static HANDLE timer = CreateWaitableTimer(NULL, FALSE, NULL);
    static double estimate = 5e-3;
    static double mean = 5e-3;
    static double m2 = 0;
    static int64_t count = 1;

    while (seconds - estimate > 1e-7) {
        double toWait = seconds - estimate;
        LARGE_INTEGER due;
        due.QuadPart = -int64_t(toWait * 1e7);
        auto start = high_resolution_clock::now();
        SetWaitableTimerEx(timer, &due, 0, NULL, NULL, NULL, 0);
        WaitForSingleObject(timer, INFINITE);
        auto end = high_resolution_clock::now();

        double observed = (end - start).count() / 1e9;
        seconds -= observed;

        ++count;
        double error = observed - toWait;
        double delta = error - mean;
        mean += delta / count;
        m2   += delta * (error - mean);
        double stddev = sqrt(m2 / (count - 1));
        estimate = mean + stddev;
    }

    // spin lock
    auto start = high_resolution_clock::now();
    while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
}
void clicker::sendclick(int& targeted_cps, FC2_TEAM_MOUSE_CODE code) {
    fc2::input::down(code);
    timerSleep(0.5 / targeted_cps);//overkill maybe
    fc2::input::up(code);
}
