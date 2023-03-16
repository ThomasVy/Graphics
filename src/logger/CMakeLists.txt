cmake_minimum_required(VERSION 3.25)

find_package(fmt REQUIRED)
add_library(logger INTERFACE)
target_include_directories(logger INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(logger INTERFACE fmt::fmt)