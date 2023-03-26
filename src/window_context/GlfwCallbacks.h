#pragma once
#include "GLFW/glfw3.h"
#include "ICallbacks.h"

namespace window_context
{
    class GlfwCallbacks : ICallbacks
    {
    public:
        GlfwCallbacks(GLFWwindow* m_window);
        void WindowSizeCallback(int width, int height) override;
    private:
        GLFWwindow* m_window;
    };
}