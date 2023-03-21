cmake_minimum_required(VERSION 3.25)

add_library(common INTERFACE)
# target_link_libraries(common INTERFACE compiler_flags)
target_include_directories(common INTERFACE "${PROJECT_SOURCE_DIR}/include")
