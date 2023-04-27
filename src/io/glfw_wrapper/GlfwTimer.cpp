#include "GlfwTimer.h"
#include "GLFW/glfw3.h"

namespace glfw_wrapper
{
    GlfwTimer::GlfwTimer()
    : m_lastTime(0)
    {
    }

    float GlfwTimer::GetMillisecondsElapsed()
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float timeElapsed = currentTime - m_lastTime;
        m_lastTime = currentTime;
        return timeElapsed;
    }
}