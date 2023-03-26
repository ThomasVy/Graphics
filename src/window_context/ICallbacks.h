#pragma once

namespace window_context
{
	class ICallbacks 
    {
    public:
        virtual void KeyCallback(int key, int scancode, int action, int mods) {}
        virtual void MouseButtonCallback(int button, int action, int mods) {}
        virtual void CursorPosCallback(double xpos, double ypos) {}
        virtual void ScrollCallback(double xoffset, double yoffset) {}
        virtual void WindowSizeCallback(int width, int height) = 0;
        virtual ~ICallbacks() = default;
    protected:
        ICallbacks& operator=(const ICallbacks&) = default; 
    };
}