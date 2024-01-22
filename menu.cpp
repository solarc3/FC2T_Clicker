#include <cstdio>
#include "menu.h"
#include "clicker.h"
#include <GLFW/glfw3.h> // Include GLF

void menu::ShowHelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
void menu::on_render(ImGuiIO& io, GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ImVec2 size = ImVec2(static_cast<float>(width), static_cast<float>(height));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
                                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("##NoTitle", nullptr, window_flags);
    if (ImGui::BeginTabBar("TabBars", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("clicker")) {
            if (ImGui::Checkbox("Left mouse clicker", &clicker::LeftClickerStatus)) {
            }
            if (clicker::LeftClickerStatus) {
                ImGui::Indent();
                ImGui::PushItemWidth(100);
                ImGui::SliderInt("Left CPS", &clicker::LeftTargetedCPS, 0, 20);
                ImGui::SameLine();
                const char *options[] = {"Hold", "Toggle"};
                static int current = 0;
                if (ImGui::Combo("##ComboLeftClicker", &current, options, IM_ARRAYSIZE(options))) {
                    printf("Current selected: %s\n", options[current]);
                }
                ImGui::Separator();
                if (ImGui::Checkbox("Spike", &clicker::LeftSpike)) {
                }
                if (clicker::LeftSpike) {
                    ImGui::Text("Spike Config");
                    ImGui::SliderInt("Spike chance", &clicker::LeftSpikeChance, 0, 100);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The chance of the spike happening in percent (%)");

                    ImGui::SliderInt("Spike amount", &clicker::LeftSpikeAmount, 0, 20);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The amount of clicks per second (CPS) that will be added to the CPS when the spike happens");
                }
                ImGui::Separator();

                if (ImGui::Checkbox("Drop", &clicker::LeftDrop)) {
                }
                if (clicker::LeftDrop) {
                    ImGui::Text("Drop Config");
                    ImGui::SliderInt("Drop chance", &clicker::LeftDropChance, 0, 100);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The chance of the drop happening in percent (%)");

                    ImGui::SliderInt("Drop amount", &clicker::LeftDropAmount, 0, 20);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The amount of clicks per second (CPS) that will be removed from the CPS when the drop happens");
                }

                ImGui::Unindent();
            }
            ImGui::Separator();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("stats")) {
            ImGui::Text("TODO: Not part of the first release :(");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}