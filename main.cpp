#include <thread>
#include "main.h"
#include "menu.h"
#include "checks.h"
#include "../fc2.hpp"
#include "clicker.h"

int main() {
    if (checks::protectionLevel()) {
        menu::start(400, 400, "FC2T_clicker");
    }
    return 0;
}