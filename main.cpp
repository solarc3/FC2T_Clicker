#include <thread>
#include "main.h"
#include "menu.h"
#include "checks.h"
#include "../fc2.hpp"
#include "clicker.h"

int main() {
    // Create and detach the background thread
    if (checks::protectionLevel()) {
        // Start the menu if protection level is adequate
        clicker::startBackgroundTask();
        menu::start(400, 600, "FC2T_clicker");
    } else {
        // Log a message if protection level is insufficient
        fc2::lua("fantasy.log(\"Cant run clicker as you don't meet the minimum protection level\")");
    }

    return 0;
}