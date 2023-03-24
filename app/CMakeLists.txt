cmake_minimum_required(VERSION 3.25)

add_executable(app main.cpp)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(app PUBLIC math filesystem logger renderer opengl_wrapper str_utils compiler_flags GLEW::GLEW glfw)
target_include_directories(app PRIVATE "${PROJECT_BINARY_DIR}")