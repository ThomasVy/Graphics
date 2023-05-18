#pragma once
#include <functional>
namespace io
{
class ITextDisplay
{
public:
    virtual ~ITextDisplay() = default;
    virtual void RenderTextWindows() = 0;
    virtual void AddTextWindow(uint32_t textWindowId, std::function<void()> textWindow) = 0;
};  
} // namespace io
