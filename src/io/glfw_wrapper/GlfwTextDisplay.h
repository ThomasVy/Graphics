#pragma once
#include "ITextDisplay.h"
#include <string_view>
#include "GLFW/glfw3.h"

namespace glfw_wrapper
{
class GlfwTextDisplay : public io::ITextDisplay
{
public:
    GlfwTextDisplay(std::string_view glslVersion, GLFWwindow* glfwWindow);
    ~GlfwTextDisplay();
    void Render() override;
};  
} // namespace glfw_wrapper