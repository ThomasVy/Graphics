cmake_minimum_required(VERSION 3.25)

add_library(graphics_api IGraphicsApi.cpp)
find_package(GLEW REQUIRED)
add_subdirectory(opengl_wrapper)

target_link_libraries(graphics_api PRIVATE logger filesystem compiler_flags GLEW::GLEW math opengl_wrapper)
target_include_directories(graphics_api INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/graphics_api")
