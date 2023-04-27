#pragma once
namespace io
{
class ITimer
{
public:
    virtual ~ITimer() = default;
    virtual float GetMillisecondsElapsed() = 0;
};
} // namespace io
