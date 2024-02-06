#include <cstdio>
#include "menu.h"
#include "clicker.h"
#include "jitter.h"
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
void menu::on_render(ImGuiIO &io, HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);
    ImVec2 size = ImVec2(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
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
                ImGui::SliderInt("Left CPS", &clicker::LeftTargetedCPS, 1, 15);
                ImGui::SameLine();
                if (ImGui::Combo("##ComboLeftClicker", &clicker::current, clicker::options,
                                 IM_ARRAYSIZE(clicker::options))) {
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
                    menu::ShowHelpMarker("The chance of the spike happening (%)");

                    ImGui::SliderInt("Spike amount##left", &clicker::LeftSpikeAmount, 0, 5);
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
                    menu::ShowHelpMarker("The chance of the drop happening (%)");

                    ImGui::SliderInt("Drop amount##left", &clicker::LeftDropAmount, 0, 5);
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
                ImGui::SliderInt("Right CPS", &clicker::RightTargetedCPS, 1, 15);
                ImGui::SameLine();

                if (ImGui::Combo("##ComboRightClicker", &clicker::rightCurrent, clicker::rightOptions, IM_ARRAYSIZE(clicker::rightOptions))) {
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
                    menu::ShowHelpMarker("The chance of the spike happening (%)");
                    ImGui::SliderInt("Spike amount##right", &clicker::RightSpikeAmount, 0, 5);
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
                    menu::ShowHelpMarker("The chance of the drop happening (%)");

                    ImGui::SliderInt("Drop amount##right", &clicker::RightDropAmount, 0, 5);
                    ImGui::SameLine();
                    menu::ShowHelpMarker(
                            "The amount of clicks per second (CPS) that will be removed from the CPS when the drop happens");
                }
                ImGui::Unindent();
            }
            ImGui::SeparatorText("Jitter Config");
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
                ImGui::SliderInt("Speed##left", &jitter::LeftJitterSpeed, 0, 100);
                ImGui::SameLine();
                menu::ShowHelpMarker(
                        "The speed at which the jitter will happen, the lower the number the faster it will happen(ms)");
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
                ImGui::SliderInt("Speed##right", &jitter::RightJitterSpeed, 0, 100);
                ImGui::SameLine();
                menu::ShowHelpMarker(
                        "The speed at which the jitter will happen, the lower the number the faster it will happen(ms)");
                ImGui::Unindent();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("misc")) {
            if(ImGui::Button("setup zombie/fc2k")){
                fc2::setup();
            }
            ImGui::PushItemWidth(130);
            ImGui::InputInt("Jitter/Drop duration", &clicker::EventDuration);
            ImGui::SameLine();
            menu::ShowHelpMarker("The duration of the event in seconds\ndefault is 5s");
            if (clicker::EventDuration < 0) {
                clicker::EventDuration = 0;
            }
            ImGui::InputInt("Global update time", &clicker::GlobalSleep);
            ImGui::SameLine();
            menu::ShowHelpMarker("This will hold updating the CPS for its duration\ndefault is 300ms");
            if (clicker::GlobalSleep < 0) {
                clicker::GlobalSleep = 0;
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

