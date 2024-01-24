#include <cstdio>
#include "menu.h"
#include "clicker.h"
#include "jitter.h"
#include <GLFW/glfw3.h>

void menu::ShowHelpMarker(const char *desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void menu::on_render(ImGuiIO &io, GLFWwindow *window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ImVec2 size = ImVec2(static_cast<float>(width), static_cast<float>(height));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("##NoTitle", nullptr, window_flags);
    if (ImGui::BeginTabBar("TabBars", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("clicker")) {
            ImGui::SeparatorText("Clicker Config");
            if (ImGui::Checkbox("Left mouse clicker", &clicker::LeftClickerStatus)) {
            }
            if (clicker::LeftClickerStatus) {
                ImGui::Indent();
                clicker::KeySelectionCombo("Left Clicker Key", clicker::Leftclickerkey);
                ImGui::PushItemWidth(100);
                ImGui::SliderInt("Left CPS", &clicker::LeftTargetedCPS, 0, 20);
                ImGui::SameLine();
                const char *options[] = {"Hold", "Toggle"};
                static int current = 0;
                if (ImGui::Combo("##ComboLeftClicker", &current, options, IM_ARRAYSIZE(options))) {
                    printf("Current selected: %s\n", options[current]);
                }
                ImGui::SliderInt("Left Clicker Range", &clicker::LeftClickerRange, 0, 5);
                ImGui::SameLine();
                menu::ShowHelpMarker("The range of CPS variation, default is 2.");
                ImGui::Separator();
                if (ImGui::Checkbox("Spike", &clicker::LeftSpike)) {
                }
                if (clicker::LeftSpike) {
                    ImGui::Text("Spike Config");
                    ImGui::SliderInt("Spike chance##left", &clicker::LeftSpikeChance, 0, 100);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The chance of the spike happening in percent (%)");

                    ImGui::SliderInt("Spike amount##left", &clicker::LeftSpikeAmount, 0, 20);
                    ImGui::SameLine();
                    menu::ShowHelpMarker(
                            "The amount of clicks per second (CPS) that will be added to the CPS when the spike happens");
                }
                ImGui::Separator();
                if (ImGui::Checkbox("Drop##left", &clicker::LeftDrop)) {
                }
                if (clicker::LeftDrop) {
                    ImGui::Text("Drop Config");
                    ImGui::SliderInt("Drop chance##left", &clicker::LeftDropChance, 0, 100);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The chance of the drop happening in percent (%)");

                    ImGui::SliderInt("Drop amount##left", &clicker::LeftDropAmount, 0, 20);
                    ImGui::SameLine();
                    menu::ShowHelpMarker(
                            "The amount of clicks per second (CPS) that will be removed from the CPS when the drop happens");
                }
                ImGui::Unindent();
            }
            if (ImGui::Checkbox("Right mouse clicker", &clicker::RightClickerStatus)) {
            }
            if (clicker::RightClickerStatus) {
                ImGui::Indent();
                clicker::KeySelectionCombo("Right Clicker Key", clicker::Rightclickerkey);
                ImGui::PushItemWidth(100);
                ImGui::SliderInt("Right CPS", &clicker::RightTargetedCPS, 0, 20);
                ImGui::SameLine();
                const char *rightOptions[] = {"Hold", "Toggle"};
                static int rightCurrent = 0;
                if (ImGui::Combo("##ComboRightClicker", &rightCurrent, rightOptions, IM_ARRAYSIZE(rightOptions))) {
                    printf("Current selected: %s\n", rightOptions[rightCurrent]);
                }
                ImGui::SliderInt("Right Clicker Range", &clicker::RightClickerRange, 0, 5);
                ImGui::SameLine();
                menu::ShowHelpMarker("The range of CPS variation, default is 2.");
                ImGui::Separator();
                if (ImGui::Checkbox("Spike##right", &clicker::RightSpike)) {
                }
                if (clicker::RightSpike) {
                    ImGui::Text("Spike Config");
                    ImGui::SliderInt("Spike chance##right", &clicker::RightSpikeChance, 0, 100);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The chance of the spike happening in percent (%)");
                    ImGui::SliderInt("Spike amount##right", &clicker::RightSpikeAmount, 0, 20);
                    ImGui::SameLine();
                    menu::ShowHelpMarker(
                            "The amount of clicks per second (CPS) that will be added to the CPS when the spike happens");
                }
                ImGui::Separator();
                if (ImGui::Checkbox("Drop", &clicker::RightDrop)) {
                }
                if (clicker::RightDrop) {
                    ImGui::Text("Drop Config");
                    ImGui::SliderInt("Drop chance##right", &clicker::RightDropChance, 0, 100);
                    ImGui::SameLine();
                    menu::ShowHelpMarker("The chance of the drop happening in percent (%)");

                    ImGui::SliderInt("Drop amount##right", &clicker::RightDropAmount, 0, 20);
                    ImGui::SameLine();
                    menu::ShowHelpMarker(
                            "The amount of clicks per second (CPS) that will be removed from the CPS when the drop happens");
                }
                ImGui::Unindent();
            }
            ImGui::SeparatorText("Jitter Config");
            //add jitter config
            if (ImGui::Checkbox("Left Jitter", &jitter::LeftJitter)) {
            }
            if (jitter::LeftJitter) {
                ImGui::Indent();
                ImGui::Text("Jitter Config");
                ImGui::PushItemWidth(100);
                ImGui::SliderInt("Intensity##left", &jitter::LeftJitterAmount, 0, 20);
                ImGui::SameLine();
                menu::ShowHelpMarker(
                        "The amount of movement that will be added, the higher the number the more the screen will \"jump\" around");
                ImGui::Separator();
                ImGui::Unindent();

            }
            if (ImGui::Checkbox("Right Jitter", &jitter::RightJitter)) {
            }
            if (jitter::RightJitter) {
                ImGui::Indent();
                ImGui::Text("Jitter Config");
                ImGui::PushItemWidth(100);
                ImGui::SliderInt("Intensity##right", &jitter::RightJitterAmount, 0, 20);
                ImGui::SameLine();
                menu::ShowHelpMarker(
                        "The amount of movement that will be added, the higher the number the more the screen will \"jump\" around");
                ImGui::Unindent();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("stats")) {
            ImGui::Text("TODO: Not part of the first release :("); //TODO: Add stats
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

