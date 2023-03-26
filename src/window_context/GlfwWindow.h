#pragma once

#include <memory>
#include <string>
#include "IWindow.h"
#include "GLFW/glfw3.h"
#include "GlfwCallbacks.h"

namespace window_context
{
	class GlfwWindow : public IWindow
	{
	public:
		GlfwWindow(const int width, const int height, std::string_view windowTitle);
		~GlfwWindow();
		bool ShouldClose() override;
		void SwapBuffers() override;
		void PollEvents() override;
	private:
		std::unique_ptr<GLFWwindow, decltype([](GLFWwindow* window) {glfwDestroyWindow(window);})> m_glfwWindow;
		std::unique_ptr<GlfwCallbacks> m_callbacks;
	};
}