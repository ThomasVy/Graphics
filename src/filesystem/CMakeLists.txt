cmake_minimum_required(VERSION 3.25)

add_library(filesystem FileSystem.cpp IFilesystem.cpp)
target_link_libraries(filesystem PRIVATE logger compiler_flags)
target_include_directories(filesystem INTERFACE "${PROJECT_SOURCE_DIR}/include")