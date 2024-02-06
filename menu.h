//
// Created by solar on 1/20/2024.
//

#ifndef FC2T_CLICKER_MENU_H
#define FC2T_CLICKER_MENU_H

#include "imgui.h"
#include <d3d11.h>
#include <tchar.h>

namespace menu {
    //https://github.com/fantasy-cat/FC2T/blob/main/examples/imgui_vulkan/vulkan.hpp
    auto on_render(ImGuiIO &io, HWND window) -> void;

    auto start(int height_h, int width_w, const wchar_t *name) -> bool;

    void ShowHelpMarker(const char *desc);
}
#endif //FC2T_CLICKER_MENU_H
