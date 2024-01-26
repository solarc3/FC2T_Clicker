#include <thread>
#include "main.h"
#include "menu.h"
#include "checks.h"
#include "../fc2.hpp"
#include "clicker.h"

int main() {
    clicker::LeftBackgroundTask(clicker::Leftclickerkey, 1);
    clicker::RightBackgroundTask(clicker::Rightclickerkey, 0);
    menu::start(400, 400, "FC2T_clicker");
    return 0;
}