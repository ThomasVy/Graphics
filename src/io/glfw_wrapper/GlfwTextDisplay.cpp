#include "GlfwTextDisplay.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include <ranges>

namespace glfw_wrapper
{
GlfwTextDisplay::GlfwTextDisplay(std::string_view glslVersion, GLFWwindow* glfwWindow)
 : m_glfwWindow(glfwWindow)
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glslVersion.data());
}

GlfwTextDisplay::~GlfwTextDisplay()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GlfwTextDisplay::AddTextWindow(uint32_t textWindowId, std::function<void()> textWindow)
{
    m_textWindows[textWindowId] = textWindow;
}

void GlfwTextDisplay::RenderTextWindows()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (const auto& textWindow : m_textWindows | std::views::values )
    {
        textWindow();
    }
    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
} // namespace glfw_wrapper
