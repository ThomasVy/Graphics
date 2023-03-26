cmake_minimum_required(VERSION 3.25)

add_library(renderer Texture.cpp Shader.cpp ShaderPipeline.cpp ShaderProgram.cpp VertexBuffer.cpp IndexBuffer.cpp VertexArray.cpp Renderer.cpp)
find_package(GLEW REQUIRED)
find_package(stb REQUIRED)
target_link_libraries(renderer PUBLIC GLEW::GLEW PRIVATE logger compiler_flags math opengl_wrapper PUBLIC stb::stb graphics_api)
target_include_directories(renderer INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/renderer")