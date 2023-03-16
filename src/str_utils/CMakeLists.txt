cmake_minimum_required(VERSION 3.25)

find_package(fmt REQUIRED)
add_library(str_utils INTERFACE)
target_include_directories(str_utils INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(str_utils INTERFACE fmt::fmt)