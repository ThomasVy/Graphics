cmake_minimum_required(VERSION 3.25)

find_package(glm REQUIRED)
add_library(math Random.cpp)
target_include_directories(math INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/math")
target_link_libraries(math PUBLIC glm::glm)