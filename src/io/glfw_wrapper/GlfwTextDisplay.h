#pragma once
#include "ITextDisplay.h"
#include <string_view>
#include <vector>

struct GLFWwindow;

namespace glfw_wrapper
{
class GlfwTextDisplay : public io::ITextDisplay
{
public:
    GlfwTextDisplay(std::string_view glslVersion, GLFWwindow* glfwWindow);
    ~GlfwTextDisplay();
    void RenderTextWindows() override;
    void AddTextWindow(uint32_t textWindowId, std::function<void()> textWindow) override;
private: 
    GLFWwindow* m_glfwWindow;
    std::unordered_map<uint32_t, std::function<void()>> m_textWindows;
};  
} // namespace glfw_wrapper