#pragma once

#include <memory>
#include <string>
#include "IWindow.h"
#include "GLFW/glfw3.h"

namespace glfw_wrapper
{
	class GlfwWindow : public io::IWindow
	{
	public:
		GlfwWindow(const int width, const int height, std::string_view windowTitle);
		~GlfwWindow();
		bool ShouldClose() override;
		void SwapBuffers() override;
		void SwitchVSync(bool condition) override;
		GLFWwindow* GetRawGlfwWindow() { return m_glfwWindow.get(); }
	private:
		std::unique_ptr<GLFWwindow, decltype([](GLFWwindow* window) {glfwDestroyWindow(window);})> m_glfwWindow;
	};
}