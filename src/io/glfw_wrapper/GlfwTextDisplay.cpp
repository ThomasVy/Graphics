#include "GlfwTextDisplay.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace glfw_wrapper
{
GlfwTextDisplay::GlfwTextDisplay(std::string_view glslVersion, GLFWwindow* glfwWindow)
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glslVersion.data());
}

GlfwTextDisplay::~GlfwTextDisplay()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void RenderFPSCounter()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("FPS Counter", nullptr, window_flags);                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("%.1f FPS (%.3f ms)", io.Framerate, 1000.0f / io.Framerate);
    ImGui::End();
}

void GlfwTextDisplay::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    {   
        RenderFPSCounter();
        //ImGui::ShowDemoWindow();
    }
    //Do all the things?
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
} // namespace glfw_wrapper
