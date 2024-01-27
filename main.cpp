#include "menu.h"
#include "clicker.h"
#include "jitter.h"

int main() {
    clicker::updateCPSTask();
    clicker::LeftBackgroundTask();
    clicker::RightBackgroundTask();
    jitter::LeftBackgroundTask();
    jitter::RightBackgroundTask();
    menu::start(400, 400, "FC2T_clicker");
    return 0;
}