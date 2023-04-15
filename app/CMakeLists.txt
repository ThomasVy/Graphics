cmake_minimum_required(VERSION 3.25)

add_executable(app main.cpp)
target_link_libraries(app PUBLIC math filesystem logger renderer opengl_wrapper str_utils compiler_flags window_context graphics_api game)
target_include_directories(app PRIVATE "${PROJECT_BINARY_DIR}")