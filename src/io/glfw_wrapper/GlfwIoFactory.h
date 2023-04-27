#pragma once
#include "IoFactory.h"

namespace glfw_wrapper
{
class GlfwWindow;
class GlfwCallbacks;
class GlfwTimer;
class GlfwTextDisplay;

class GlfwIoFactory : public io::IoFactory
{
public:
    GlfwIoFactory(const int width, const int height, std::string_view windowTitle); 
    ~GlfwIoFactory();
    io::IWindow& GetWindow() override;
    io::ICallbacks& GetControls(const std::span<std::string_view> validKeys) override;
    io::ITextDisplay& GetTextDisplay() override;
    void Refresh() override;
    io::ITimer& GetTimer() override;
private:
    std::unique_ptr<GlfwWindow> m_window;
    std::unique_ptr<GlfwCallbacks> m_callbacks;
    std::unique_ptr<GlfwTimer> m_timer;
    std::unique_ptr<GlfwTextDisplay> m_textDisplay;
};
} // namespace glfw_wrapper
