#pragma once
#include "GLFW/glfw3.h"
#include "ICallbacks.h"
#include <unordered_map>
#include <span>
#include <string_view>
namespace glfw_wrapper
{
    class GlfwCallbacks : public io::ICallbacks
    {
    public:
        GlfwCallbacks(GLFWwindow* m_window);
        void KeyCallback(int key, int scancode, int action, int mods) override;
        void ScrollCallback(double xoffset, double yoffset) override;
        void WindowSizeCallback(int width, int height) override;
        bool IsKeyHeld(std::string_view key) override;
        void PollEvents() override;
        bool WasKeyPressed(std::string_view key) override;
        void Clear() override
        {
            m_scrollDelta = 0.0f;
        }
        inline double GetScrollDelta() override
        {
            return m_scrollDelta;
        }
    private:
        double m_scrollDelta = 0.0f;
        std::unordered_map<int, bool> m_keyMap;
    };
}