cmake_minimum_required(VERSION 3.25)

add_library(renderer CreateShapes.cpp Texture.cpp Shader.cpp ShaderPipeline.cpp ShaderProgram.cpp IndexBuffer.cpp Renderer.cpp)
find_package(stb REQUIRED)
target_link_libraries(renderer PRIVATE logger compiler_flags math PUBLIC stb::stb graphics_api opengl_wrapper)
target_include_directories(renderer INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/renderer")