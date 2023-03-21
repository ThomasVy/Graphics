cmake_minimum_required(VERSION 3.25)

add_library(graphics IGraphicsApi.cpp)
find_package(GLEW REQUIRED)
target_link_libraries(graphics PRIVATE logger filesystem compiler_flags GLEW::GLEW math)
target_include_directories(graphics INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/graphics")
