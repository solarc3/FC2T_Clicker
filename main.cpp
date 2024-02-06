#include "menu.h"
#include "clicker.h"
#include "jitter.h"

int main() {
    clicker::updateCPSTask();
    clicker::BackgroundTask();
    jitter::LeftBackgroundTask();
    jitter::RightBackgroundTask();
    menu::start(400, 400, L"FC2T_clicker");
    return 0;
}