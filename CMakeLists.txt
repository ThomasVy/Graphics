cmake_minimum_required(VERSION 3.25)

project(Project VERSION 1.0)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_23)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(res/textures/ship.png textures/ship.png COPYONLY)
configure_file(res/textures/diamond.png textures/diamond.png COPYONLY)
configure_file(res/textures/fire.png textures/fire.png COPYONLY)
configure_file(res/textures/tilemap_packed.png textures/tilemap_packed.png COPYONLY)

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(app)

configure_file(Config.h.in Config.h)