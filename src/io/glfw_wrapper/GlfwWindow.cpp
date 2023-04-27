#include "GlfwWindow.h"
#include "logger/Log.h"
#include <stdexcept>
#include "GlfwCallbacks.h"
namespace glfw_wrapper
{
    GlfwWindow::GlfwWindow(const int width, const int height, std::string_view windowTitle)
    { 
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        m_glfwWindow.reset(glfwCreateWindow(width, height, windowTitle.data(), nullptr, nullptr));
        if (!m_glfwWindow) {
            logger::Error("WINDOW failed to create GLFW window");
            throw std::runtime_error("Failed to create GLFW window.");
	    }
	    glfwMakeContextCurrent(m_glfwWindow.get());
    }

    bool GlfwWindow::ShouldClose()
    {
        return glfwWindowShouldClose(m_glfwWindow.get()); 
    }

    void GlfwWindow::SwapBuffers() 
    { 
        glfwSwapBuffers(m_glfwWindow.get()); 
    }

    GlfwWindow::~GlfwWindow()
    {
        glfwTerminate();
    }

    void GlfwWindow::SwitchVSync(bool condition)
    {
        glfwSwapInterval(condition ? 1 : 0);
    }
}
