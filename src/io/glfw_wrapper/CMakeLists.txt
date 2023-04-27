cmake_minimum_required(VERSION 3.25)

add_library(glfw_wrapper GlfwIoFactory.cpp GlfwCallbacks.cpp GlfwWindow.cpp GlfwTimer.cpp GlfwTextDisplay.cpp)
find_package(glfw3 REQUIRED)
find_package(imgui)
target_link_libraries(glfw_wrapper PRIVATE logger compiler_flags glfw imgui::imgui imgui_bindings)
target_include_directories(glfw_wrapper INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/io")