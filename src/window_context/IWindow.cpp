#include "IWindow.h"
#include "GlfwWindow.h"
std::unique_ptr<window_context::IWindow> window_context::GetWindow(const int width, const int height, std::string_view windowTitle)
{
    return std::make_unique<GlfwWindow>(width, height, windowTitle);
}