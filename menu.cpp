#include <cstdio>
#include "menu.h"
#include "../fc2.hpp"
auto menu::on_render(ImGuiIO& io, HWND hwnd) -> void {
    if( fc2::get_error() != FC2_TEAM_ERROR_NO_ERROR)
    {
        puts("Universe4 is not running or is unresponsive.");
        std::exit( 1 );
    }
    RECT rect;
    GetClientRect(hwnd, &rect);
    ImVec2 size = ImVec2(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top));
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
            // Content for Tab 1

            // Variables to hold the state
            int currentKey = 0; // Replace with your actual key variable
            const char* modes[] = { "Hold", "Click" ,"Toogle"};
            int currentMode = 0; // 0 for Hold, 1 for Click
            ImGui::Text("Keybind");
            ImGui::Separator();

            // Input for the keybind
            if (ImGui::Button("Press a key")) {
                fc2::lua( "fantasy.log(\"Hello World\")" );
            }
            ImGui::SameLine(); // Continue on the same line
            const char *options[] = {"Hold", "Toogle"};
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
        if (ImGui::BeginTabItem("FC2 config")){
            ImGui::Text("member info dump");
            ImGui::SameLine();
            if(ImGui::Button("Info")){
                auto output = fc2::api("getMember&protection&beautify");
                std::puts( output.c_str() );
            }
            ImGui::EndTabItem();
        }

        // Continue adding tabs as needed

        ImGui::EndTabBar();
    }
    ImGui::End();

}

