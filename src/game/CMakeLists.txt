cmake_minimum_required(VERSION 3.25)

find_package(imgui)
add_library(game BackgroundCreation.cpp GameObject.cpp Camera.cpp TextWindows.cpp)
target_link_libraries(game PRIVATE logger compiler_flags math imgui::imgui)
target_include_directories(game INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/game")