#include "Time.h"
#include "GLFW/glfw3.h"

namespace window_context
{
float GetCurrentTimeInSeconds()
{
    return (float)glfwGetTime();
}
} // namespace window_context
