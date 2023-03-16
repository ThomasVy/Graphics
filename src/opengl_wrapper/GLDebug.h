#pragma once
#include <string_view>
#include "GL/glew.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(std::string_view function, std::string_view file, int line);