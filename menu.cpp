#include <cstdio>
#include "menu.h"
#include "clicker.h"
#include <GLFW/glfw3.h> // Include GLFW

void menu::on_render(ImGuiIO& io, GLFWwindow* window) { // Changed HWND to GLFWwindow*

    int width, height;
    glfwGetFramebufferSize(window, &width, &height); // Get window size using GLFW
    ImVec2 size = ImVec2(static_cast<float>(width), static_cast<float>(height));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("##NoTitle", nullptr, window_flags);
    /* START CONFIG HERE */
    static float f = 0.0f;
    static int counter = 0;
    ImGui::ShowDemoWindow();
    if (ImGui::BeginTabBar("TabBars", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("clicker")) {
            if (ImGui::Button("Left mouse clicker")) {
                clicker::LeftClickerStatus = true;
                ImGui::SliderInt("Left CPS", &clicker::LeftTargetedCPS, 0, 20);
            }
            ImGui::SameLine(); // Continue on the same line
            const char *options[] = {"Hold", "Toggle"};
            static int current = 0;
            if(ImGui::Combo("##NoTitle",&current,options,IM_ARRAYSIZE(options))){
                printf("Current selected: %s\n",options[current]);
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("stats")) {
            // Content for Tab 2
            ImGui::Text("This is the content of Tab 2");

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}
