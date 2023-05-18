#pragma once
#include <string_view> 

namespace io
{
	class ICallbacks 
    {
    public:
        virtual void KeyCallback(int key, int scancode, int action, int mods) {}
        virtual bool IsKeyHeld(std::string_view key) = 0;
        virtual bool WasKeyPressed(std::string_view key) = 0;
        virtual void MouseButtonCallback(int button, int action, int mods) {}
        virtual void CursorPosCallback(double xpos, double ypos) {}
        virtual void ScrollCallback(double xoffset, double yoffset) {}
        virtual void WindowSizeCallback(int width, int height) = 0;
        virtual void PollEvents() = 0;
        virtual double GetScrollDelta() = 0;
        virtual void Clear() = 0;
        virtual ~ICallbacks() = default;
    protected:
        ICallbacks& operator=(const ICallbacks&) = default; 
    };
}