#pragma once
#include <memory>
#include "IWindow.h"
#include "ICallbacks.h"
#include "ITimer.h"
#include "ITextDisplay.h"

namespace io
{

class IoFactory
{
public:
    virtual ~IoFactory() = default;
    virtual IWindow& GetWindow() = 0;
    virtual ICallbacks& GetControls() = 0;
    virtual ITimer& GetTimer() = 0;
    virtual ITextDisplay& GetTextDisplay() = 0;
    virtual void Refresh() = 0;
};

std::unique_ptr<IoFactory> GetIoFactory(const int width, const int height, std::string_view windowTitle);
    
} // namespace io