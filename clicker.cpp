#include <thread>
#include <iostream>
#include "clicker.h"
#include "imgui.h"
#include <windows.h>
#include <random>
#include <math.h>

[[noreturn]] void clicker::clicker(unsigned int &leftKeyHexValue, unsigned int &rightKeyHexValue, bool &leftClickerStatus, bool &rightClickerStatus, int &leftCurrent, int &rightCurrent) {
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    static bool leftToggleState = false, rightToggleState = false;
    static bool leftWasDown = false, rightWasDown = false;
    while (true) {
        bool isLeftKeyDown = (GetAsyncKeyState(leftKeyHexValue) & 0x8000) != 0;
        if (leftClickerStatus) {
            if (leftCurrent == 1) { // Toggle
                if (isLeftKeyDown && !leftWasDown) {
                    leftToggleState = !leftToggleState;
                    leftWasDown = true;
                } else if (!isLeftKeyDown) {
                    leftWasDown = false;
                }
            }
            if ((leftCurrent == 1 && leftToggleState) || (leftCurrent == 0 && isLeftKeyDown)) {
                clicker::sendclick(FC2_TEAM_MOUSE_LEFT, clicker::LeftcurrentCPS);
            }
        }
        bool isRightKeyDown = (GetAsyncKeyState(rightKeyHexValue) & 0x8000) != 0;
        if (rightClickerStatus) {
            if (rightCurrent == 1) { // Toggle
                if (isRightKeyDown && !rightWasDown) {
                    rightToggleState = !rightToggleState;
                    rightWasDown = true;
                } else if (!isRightKeyDown) {
                    rightWasDown = false;
                }
            }
            if ((rightCurrent == 1 && rightToggleState) || (rightCurrent == 0 && isRightKeyDown)) {
                clicker::sendclick(FC2_TEAM_MOUSE_RIGHT, clicker::RightcurrentCPS);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
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
void clicker::sendclick(FC2_TEAM_MOUSE_CODE code, int cps) {
    fc2::input::down(code);
    timerSleep(0.5/cps);
    fc2::input::up(code);
}

void sleep(int seconds){
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
int rndCPS(int currentCPS, int clickerRange) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    int minCPS = std::max(1, currentCPS - clickerRange);
    int maxCPS = currentCPS + clickerRange;
    std::uniform_int_distribution<> dis(minCPS, maxCPS);
    return dis(gen);
}
[[noreturn]] void clicker::update(int &eventDuration, int &Sleep){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    while (true) {
        clicker::LeftcurrentCPS = clicker::LeftTargetedCPS;
        clicker::RightcurrentCPS = clicker::RightTargetedCPS;
        if (clicker::LeftSpike && dis(gen) <= clicker::LeftSpikeChance) {
            clicker::LeftcurrentCPS = clicker::LeftTargetedCPS + clicker::LeftSpikeAmount;
            sleep(eventDuration);
        }
        if (clicker::RightSpike && dis(gen) <= clicker::RightSpikeChance) {
            clicker::RightcurrentCPS = clicker::RightTargetedCPS + clicker::RightSpikeAmount;
            sleep(eventDuration);
        }
        if (clicker::LeftDrop && dis(gen) <= clicker::LeftDropChance) {
            clicker::LeftcurrentCPS = clicker::LeftTargetedCPS - clicker::LeftDropAmount;
            if(clicker::LeftcurrentCPS < 0){
                clicker::LeftcurrentCPS = 1;
            }
            sleep(eventDuration);
        }
        if (clicker::RightDrop && dis(gen) <= clicker::RightDropChance) {
            clicker::RightcurrentCPS = clicker::RightTargetedCPS - clicker::RightDropAmount;
            if(clicker::RightcurrentCPS < 0){
                clicker::RightcurrentCPS = 1;
            }
            sleep(eventDuration);
        }
        //even if any of the events are disabled the cps must be updated with its range
        clicker::LeftcurrentCPS = rndCPS(clicker::LeftcurrentCPS, clicker::LeftClickerRange);
        clicker::RightcurrentCPS = rndCPS(clicker::RightcurrentCPS, clicker::RightClickerRange);
        printf("Left cps: %d, Right cps: %d\n", clicker::LeftcurrentCPS, clicker::RightcurrentCPS);
        std::this_thread::sleep_for(std::chrono::milliseconds(Sleep));
    }
}

void clicker::updateCPSTask(){
    std::jthread bgThread([]() {update(clicker::EventDuration, clicker::GlobalSleep);});
    bgThread.detach();
}
void clicker::BackgroundTask() {
    std::jthread bgThread([]() {clicker(clicker::Leftclickerkey,clicker::Rightclickerkey, clicker::LeftClickerStatus,clicker::RightClickerStatus,clicker::current, clicker::rightCurrent);});
    bgThread.detach();
}