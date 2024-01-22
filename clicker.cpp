#include <thread>
#include <iostream>
#include "clicker.h"

namespace clicker {
    void backgroundTask() {
        while (true) {
            if(clicker::LeftClickerStatus){
                std::cout << "Left clicker is enabled" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Example delay
            }
            else{
                std::cout << "Left clicker is disabled" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Example delay
            }
            // Perform task
        }
    }
    void startBackgroundTask() {
        // Start the background task in a new thread
        std::jthread bgThread(backgroundTask);
        bgThread.detach(); // Detach the thread to run independently
    }
}
