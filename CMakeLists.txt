cmake_minimum_required(VERSION 3.0)

# Name your project here
project(FC2T_Clicker)

# Set C++20 as the language standard for the project
set(CMAKE_CXX_STANDARD 20)

# If you have any include directories add them here
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
        # Add any additional include directories here
)

# Find the necessary packages
#find_package(glfw3 REQUIRED)
#find_package(Vulkan REQUIRED)
#find_package(DirectX REQUIRED)

# Add the source files you want to compile
file(GLOB IMGUI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp)
add_executable(${PROJECT_NAME}
        ${IMGUI_SOURCES}
        dx11.cpp
        menu.cpp
        main.cpp
        clicker.cpp
)

# Link against the libraries you need here
target_link_libraries(${PROJECT_NAME}
 #       glfw
#        Vulkan::Vulkan
#        d3d9
        d3d11
       dwmapi
       d3dcompiler
#        dxgi
#        # Add any additional libraries here
)

# If ImGui requires any preprocessor definitions or compiler options, add them here
