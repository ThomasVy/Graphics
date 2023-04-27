#include "GlfwIoFactory.h"
#include "GlfwTimer.h"
#include "GlfwWindow.h"
#include "GlfwCallbacks.h"
#include "GlfwTextDisplay.h"

namespace glfw_wrapper
{
GlfwIoFactory::GlfwIoFactory(const int width, const int height, std::string_view windowTitle)
    : m_window(std::make_unique<GlfwWindow>(width, height, windowTitle))
    , m_callbacks(std::make_unique<GlfwCallbacks>(m_window->GetRawGlfwWindow()))
    , m_timer(std::make_unique<GlfwTimer>())
    , m_textDisplay(std::make_unique<GlfwTextDisplay>("#version 460", m_window->GetRawGlfwWindow()))
{
}

GlfwIoFactory::~GlfwIoFactory()
{
}

io::IWindow& GlfwIoFactory::GetWindow()
{
    return *m_window;
}

io::ICallbacks& GlfwIoFactory::GetControls(const std::span<std::string_view> validKeys)
{
    m_callbacks->SetValidKeys(validKeys);
    return *m_callbacks;
}

io::ITextDisplay& GlfwIoFactory::GetTextDisplay()
{
    return *m_textDisplay;
}

void GlfwIoFactory::Refresh()
{
    m_window->SwapBuffers();
    m_callbacks->PollEvents();
}

io::ITimer& GlfwIoFactory::GetTimer()
{
    return *m_timer;
}
} // namespace glfw_wrapper

