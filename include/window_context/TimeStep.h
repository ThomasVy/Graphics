#pragma once

namespace window_context
{
class Timestep
{
public:
    Timestep(float time =0.0f)
        : m_time(time)
    {}

    inline operator float()const {return m_time;}

    inline float GetSeconds() const { return m_time;}
    inline float GetMilliseconds() const { return m_time;}
private:
    float m_time;
};

float GetCurrentTimeInSeconds();

} // namespace window_context
