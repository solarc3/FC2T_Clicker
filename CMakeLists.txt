cmake_minimum_required(VERSION 3.0)
project(FC2T_Clicker)
set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
set(LIBRARIES "glfw;Vulkan::Vulkan")
file(GLOB IMGUI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp)
add_executable(${PROJECT_NAME}
        ${IMGUI_SOURCES}
        main.cpp
        menu.cpp
        vulkan.cpp
        clicker.cpp
        jitter.cpp
)
target_link_libraries(FC2T_Clicker ${LIBRARIES} dwmapi)