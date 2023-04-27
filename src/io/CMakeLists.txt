cmake_minimum_required(VERSION 3.25)

add_library(io IoFactory.cpp)

add_subdirectory(glfw_wrapper)

target_link_libraries(io PRIVATE logger compiler_flags glfw_wrapper)
target_include_directories(io INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/io")