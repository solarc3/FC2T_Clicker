//
// Created by solar on 1/20/2024.
//

#ifndef FC2T_CLICKER_MENU_H
#define FC2T_CLICKER_MENU_H
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

namespace menu {
    //using https://github.com/fantasy-cat/FC2T/blob/main/examples/imgui_vulkan/vulkan.hpp
    void on_render(ImGuiIO & io );
    auto start(int height, int width,const wchar_t * name) -> bool; //required bool return, constant char for the name
}


#endif //FC2T_CLICKER_MENU_H
