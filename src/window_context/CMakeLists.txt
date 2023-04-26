cmake_minimum_required(VERSION 3.25)

add_library(window_context GlfwCallbacks.cpp GlfwWindow.cpp IWindow.cpp TimeStep.cpp)
find_package(glfw3 REQUIRED)
target_link_libraries(window_context PRIVATE logger compiler_flags glfw)
target_include_directories(window_context INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/window_context")