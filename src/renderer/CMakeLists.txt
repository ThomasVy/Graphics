cmake_minimum_required(VERSION 3.25)

add_library(renderer VertexBuffer.cpp IndexBuffer.cpp VertexArray.cpp)
find_package(GLEW REQUIRED)
target_link_libraries(renderer PRIVATE logger compiler_flags GLEW::GLEW math opengl_wrapper)
target_include_directories(renderer INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/renderer")