#pragma once
#include "ITimer.h"
namespace glfw_wrapper
{
class GlfwTimer : public io::ITimer
{
public:
    GlfwTimer();
    float GetMillisecondsElapsed() override;
private:
    float m_lastTime;
};
} // namespace 
