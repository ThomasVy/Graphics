cmake_minimum_required(VERSION 3.25)

find_package(imgui)
find_package(glfw3 REQUIRED)

add_library(imgui_bindings imgui_impl_glfw.cpp imgui_impl_opengl3.cpp)
target_link_libraries(imgui_bindings PRIVATE compiler_flags imgui::imgui glfw)
target_include_directories(imgui_bindings INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
