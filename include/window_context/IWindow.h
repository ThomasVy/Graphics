#pragma once
#include <memory>
#include <string_view>
namespace window_context
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;
        virtual bool ShouldClose() = 0;
		virtual void SwapBuffers() = 0;
        virtual void PollEvents() = 0;
        virtual void SwitchVSync(bool condition) = 0;
    protected:
        IWindow& operator=(const IWindow&) = default; 
    };

    std::unique_ptr<IWindow> GetWindow(const int width, const int height, std::string_view windowTitle);
}