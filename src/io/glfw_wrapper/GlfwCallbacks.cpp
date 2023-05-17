#include "GlfwCallbacks.h"
#include <array>
#include "common/ConstExprMap.h"
#include "logger/Log.h"
namespace
{
    void KeyMetaCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* callbacks = static_cast<io::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->KeyCallback(key, scancode, action, mods);
    }


    void MouseButtonMetaCallback(GLFWwindow* window, int button, int action, int mods) {
        auto* callbacks = static_cast<io::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->MouseButtonCallback(button, action, mods);
    }


    void CursorPosMetaCallback(GLFWwindow* window, double xpos, double ypos) {
        auto* callbacks = static_cast<io::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->CursorPosCallback(xpos, ypos);
    }


    void ScrollMetaCallback(GLFWwindow* window, double xoffset, double yoffset) {
        auto* callbacks = static_cast<io::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->ScrollCallback(xoffset, yoffset);
    }


    void WindowSizeMetaCallback(GLFWwindow* window, int width, int height) {
        auto* callbacks = static_cast<io::ICallbacks*>(glfwGetWindowUserPointer(window));
        callbacks->WindowSizeCallback(width, height);
    }
    using namespace std::string_view_literals;
    constexpr std::array LETTER_TO_GLFW_KEY
    {
        std::make_pair("A"sv, GLFW_KEY_A),
        std::make_pair("S"sv, GLFW_KEY_S),
        std::make_pair("W"sv, GLFW_KEY_W),
        std::make_pair("D"sv, GLFW_KEY_D),
        std::make_pair("Q"sv, GLFW_KEY_Q)
    };

    constexpr common::ConstExprMap KEY_LOOKUP{
        LETTER_TO_GLFW_KEY
    };
}


namespace glfw_wrapper
{
    GlfwCallbacks::GlfwCallbacks(GLFWwindow* window)
        : m_keyMap()
    {
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, KeyMetaCallback);
        glfwSetMouseButtonCallback(window, MouseButtonMetaCallback);
        glfwSetCursorPosCallback(window, CursorPosMetaCallback);
        glfwSetScrollCallback(window, ScrollMetaCallback);
        glfwSetWindowSizeCallback(window, WindowSizeMetaCallback);  
    }

    void GlfwCallbacks::KeyCallback(int key, int scancode, int action, int mods)
    {
        if (!m_keyMap.contains(key))
            return;

        if (action == GLFW_PRESS) {
			m_keyMap[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			m_keyMap[key] = false;
		}
    }
    
    void GlfwCallbacks::ScrollCallback(double xoffset, double yoffset)
    {
        m_scrollDelta = yoffset;
    }

    void GlfwCallbacks::WindowSizeCallback(int width, int height)
    {
        glViewport(0, 0, width, height); 
    }
    
    bool GlfwCallbacks::IsKeyHeld(std::string_view key)
    {
        auto glfwKey = KEY_LOOKUP.at(key);
        if (!m_keyMap.contains(glfwKey))
            return false;
        return m_keyMap[glfwKey];
    }
    
    void GlfwCallbacks::SetValidKeys(const std::span<std::string_view> validKeys)
    {
        m_keyMap.clear();
        for (const auto key : validKeys)
        {
            auto glfwKey = KEY_LOOKUP.at(key);
            m_keyMap[glfwKey] = false;
        }
    }
    
    void GlfwCallbacks::PollEvents()
    {
        glfwPollEvents();
    }
    
    bool GlfwCallbacks::WasKeyPressed(std::string_view key)
    {
        auto glfwKey = KEY_LOOKUP.at(key);
        if (!m_keyMap.contains(glfwKey))
            return false;
        auto res = m_keyMap[glfwKey];
        m_keyMap[glfwKey] = false;
        return res;
    }
} // namespace 
