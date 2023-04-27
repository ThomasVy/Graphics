#pragma once
namespace io
{
class ITextDisplay
{
public:
    virtual ~ITextDisplay() = default;
    virtual void Render() = 0;
};  
} // namespace io
