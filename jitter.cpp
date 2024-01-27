#include "jitter.h"
#include "clicker.h"
#include <random>

[[noreturn]] void jitter::move(FC2_TEAM_MOUSE_CODE code, unsigned int &keyHexValue, int &current){
    static std::random_device rd;
    static std::knuth_b gen(rd());
    static bool toggleState = false;
    static bool wasDown = false;
    while (true) {
        bool isKeyDown = (GetAsyncKeyState(keyHexValue) & 0x8000) != 0;
        if (current == 1) {
            if (isKeyDown && !wasDown) {
                toggleState = !toggleState;
                wasDown = true;
            } else if (!isKeyDown) {
                wasDown = false;
            }
        }
        bool applyJitter = false;
        if (current == 1  && toggleState) {
            applyJitter = true;
        } else if (current == 0 && isKeyDown) {
            applyJitter = true;
        }
        if (applyJitter) {
            int jitterAmount = (code == FC2_TEAM_MOUSE_LEFT) ? jitter::LeftJitterAmount : jitter::RightJitterAmount;
            std::uniform_int_distribution<> dis(-jitterAmount, jitterAmount);
            int x = dis(gen);
            int y = dis(gen);
            fc2::input::move(x, y);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void jitter::LeftBackgroundTask() {
    std::jthread bgThread([]() {move(FC2_TEAM_MOUSE_LEFT, clicker::Leftclickerkey,clicker::current);});
    bgThread.detach();
}
void jitter::RightBackgroundTask() {
    std::jthread bgThread([]() {move(FC2_TEAM_MOUSE_RIGHT, clicker::Rightclickerkey,clicker::rightCurrent);});
    bgThread.detach();
}