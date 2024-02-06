cmake_minimum_required(VERSION 3.27)
project(FC2T_Clicker)
set(CMAKE_CXX_STANDARD 20)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
file(GLOB IMGUI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp)
add_executable(${PROJECT_NAME}
        ${IMGUI_SOURCES}
        main.cpp
        menu.cpp
        clicker.cpp
        jitter.cpp
        dx11.cpp
)
target_link_libraries(${PROJECT_NAME} dwmapi d3d11 dxgi d3dcompiler)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
