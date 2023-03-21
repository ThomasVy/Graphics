cmake_minimum_required(VERSION 3.25)

find_package(glm REQUIRED)
add_library(math INTERFACE)
target_include_directories(math INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(math INTERFACE glm::glm)