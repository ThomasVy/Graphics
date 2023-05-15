cmake_minimum_required(VERSION 3.25)

add_library(game GameObject.cpp Camera.cpp)
target_link_libraries(game PRIVATE logger compiler_flags math )
target_include_directories(game INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/game")