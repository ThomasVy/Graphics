#pragma once
#include "math/MatrixAndVectorMath.h"
#include "window_context/TimeStep.h"

namespace game
{
class GameObject
{
public:
    GameObject(float scale, my_math::vec3 position, float heading);
    my_math::mat4 GetModel() const;
    void Update(window_context::Timestep timestep);

private:
    float m_scale;
    my_math::vec3 m_position;
    float m_heading;
};
} // namespace game
