#include "GlfwCallbacks.h"

namespace
{
    void KeyMetaCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* callbacks = static_cast<window_context::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->KeyCallback(key, scancode, action, mods);
    }


    void MouseButtonMetaCallback(GLFWwindow* window, int button, int action, int mods) {
        auto* callbacks = static_cast<window_context::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->MouseButtonCallback(button, action, mods);
    }


    void CursorPosMetaCallback(GLFWwindow* window, double xpos, double ypos) {
        auto* callbacks = static_cast<window_context::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->CursorPosCallback(xpos, ypos);
    }


    void ScrollMetaCallback(GLFWwindow* window, double xoffset, double yoffset) {
        auto* callbacks = static_cast<window_context::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->ScrollCallback(xoffset, yoffset);
    }


    void WindowSizeMetaCallback(GLFWwindow* window, int width, int height) {
        auto* callbacks = static_cast<window_context::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->WindowSizeCallback(width, height);
    }

}


namespace window_context
{
    GlfwCallbacks::GlfwCallbacks(GLFWwindow* window)
        : m_window{window}
    {
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, KeyMetaCallback);
        glfwSetMouseButtonCallback(window, MouseButtonMetaCallback);
        glfwSetCursorPosCallback(window, CursorPosMetaCallback);
        glfwSetScrollCallback(window, ScrollMetaCallback);
        glfwSetWindowSizeCallback(window, WindowSizeMetaCallback);  
    }

    void GlfwCallbacks::WindowSizeCallback(int width, int height)
    {
        glViewport(0, 0, width, height); 
    }
} // namespace window_context
