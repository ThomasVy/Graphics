#include "IoFactory.h"
#include "glfw_wrapper/GlfwIoFactory.h"

namespace io
{
std::unique_ptr<IoFactory> GetIoFactory(const int width, const int height, std::string_view windowTitle)
{
    return std::make_unique<glfw_wrapper::GlfwIoFactory>(width, height, windowTitle);
}   
} // namespace io
