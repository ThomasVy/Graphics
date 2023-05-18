#include "TextWindows.h"
#include "imgui.h"

namespace game
{
    void RenderFPSCounter()
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
    void RenderControlsHelp()
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
        window_flags |= ImGuiWindowFlags_NoResize;

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::Begin("Controls", nullptr, window_flags);
        ImGui::Text("WASD - Move ");
        ImGui::Text("LEFT SHIFT - Run");
        ImGui::Text("Scroll Wheel - Zoom");
        ImGui::Text("Q - Toggle Wireframe");
        ImGui::Text("E - Toggle Player Textures");
        ImGui::End();
    }
} // namespace game
