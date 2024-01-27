#include <thread>
#include <iostream>
#include "clicker.h"
#include "imgui.h"
#include "jitter.h"
#include <windows.h>
#include <random>
#include <math.h>

[[noreturn]] void clicker::BackgroundTask(unsigned int &keyHexValue, bool &clickerStatus, int &current, bool &Jitter, FC2_TEAM_MOUSE_CODE code) {
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
                            clicker::sendclick(code);
                            printf("i should be moving!!!");
                            jitter::move(code, keyHexValue, current);
                    }
                    else {
                        if(toggleState){
                            clicker::sendclick(code);}
                        break;
                    }
                break;
                case 0: // Hold
                    if (Jitter && isKeyDown) {
                        clicker::sendclick(code);
                        printf("i should be moving!!");
                        jitter::move(code, keyHexValue, current);
                    } else {
                        if (isKeyDown) {
                            clicker::sendclick(code);
                        }
                        break;
                    }
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
void clicker::LeftBackgroundTask() {
    std::jthread bgThread([]() {BackgroundTask(clicker::Leftclickerkey, clicker::LeftClickerStatus, clicker::current, jitter::LeftJitter, FC2_TEAM_MOUSE_LEFT);});
    bgThread.detach();
}
void clicker::RightBackgroundTask() {
    std::jthread bgThread([]() {BackgroundTask(clicker::Rightclickerkey, clicker::RightClickerStatus, clicker::rightCurrent, jitter::RightJitter, FC2_TEAM_MOUSE_RIGHT);});
    bgThread.detach();
}
void clicker::updateCPSTask(){
    std::jthread bgThread([]() {update(clicker::EventDuration, clicker::GlobalSleep);});
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
void clicker::sendclick(FC2_TEAM_MOUSE_CODE code) {
    if (code == FC2_TEAM_MOUSE_LEFT){
        int cps = clicker::LeftcurrentCPS;
        printf("Ding! cps is: %d\n", cps);
        printf("Sleeping for: %f\n", 0.5 / cps);
        fc2::input::down(FC2_TEAM_MOUSE_LEFT);
        timerSleep(0.5 / cps);//overkill maybe
        fc2::input::up(FC2_TEAM_MOUSE_LEFT);
    }
    if(code == FC2_TEAM_MOUSE_RIGHT){
        int cps = clicker::RightcurrentCPS;
        fc2::input::down(FC2_TEAM_MOUSE_RIGHT);
        timerSleep(0.5 / cps);//overkill maybe
        fc2::input::up(FC2_TEAM_MOUSE_RIGHT);
    }
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
    //probably the incorrect way to handle all of this, might need to redo
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
            sleep(eventDuration);
        }

        if (clicker::RightDrop && dis(gen) <= clicker::RightDropChance) {
            clicker::RightcurrentCPS = clicker::RightTargetedCPS - clicker::RightDropAmount;
            sleep(eventDuration);
        }
        //even if any of the events are disabled the cps must be updated with its range
        clicker::LeftcurrentCPS = rndCPS(clicker::LeftcurrentCPS, clicker::LeftClickerRange);
        clicker::RightcurrentCPS = rndCPS(clicker::RightcurrentCPS, clicker::RightClickerRange);

        printf("Left cps: %d, Right cps: %d\n", clicker::LeftcurrentCPS, clicker::RightcurrentCPS);
        std::this_thread::sleep_for(std::chrono::milliseconds(Sleep));
    }
}