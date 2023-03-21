cmake_minimum_required(VERSION 3.25)

add_library(opengl_wrapper GLDebug.cpp)
find_package(GLEW REQUIRED)
target_link_libraries(opengl_wrapper PRIVATE compiler_flags GLEW::GLEW common logger)
target_include_directories(opengl_wrapper INTERFACE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${PROJECT_SOURCE_DIR}/include/opengl_wrapper" PUBLIC
"${PROJECT_BINARY_DIR}")

# Copy all the shaders and tell the build system to re-run CMAKE if one of them changes
file(GLOB files shaders/*)
foreach(file ${files})
	get_filename_component(name ${file} NAME)
	configure_file(${file} ${CMAKE_BINARY_DIR}/shaders/${name})
endforeach()