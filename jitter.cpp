#include "jitter.h"
#include "clicker.h"
#include <random>

[[noreturn]] void jitter::move(FC2_TEAM_MOUSE_CODE code, unsigned int &keyHexValue, int &current, bool &status, int&speed){
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
        if (current == 1  && toggleState && status) {
            applyJitter = true;
        } else if (current == 0 && isKeyDown && status) {
            applyJitter = true;
        }
        if (applyJitter) {
            int jitterAmount = (code == FC2_TEAM_MOUSE_LEFT) ? jitter::LeftJitterAmount : jitter::RightJitterAmount;
            std::uniform_int_distribution<> dis(-jitterAmount, jitterAmount);
            int x = dis(gen);
            int y = dis(gen);
            fc2::input::move(x, y);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}


void jitter::LeftBackgroundTask() {
    std::jthread bgThread([]() {move(FC2_TEAM_MOUSE_LEFT, clicker::Leftclickerkey,clicker::current, jitter::LeftJitter, jitter::LeftJitterSpeed);});
    bgThread.detach();
}
void jitter::RightBackgroundTask() {
    std::jthread bgThread([]() {move(FC2_TEAM_MOUSE_RIGHT, clicker::Rightclickerkey,clicker::rightCurrent, jitter::RightJitter, jitter::RightJitterSpeed);});
    bgThread.detach();
}