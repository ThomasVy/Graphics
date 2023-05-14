#pragma once
#include "math/MatrixAndVectorMath.h"

namespace game
{
class GameObject
{
public:
    GameObject(float scale, my_math::vec3 position, float heading);
    my_math::mat4 GetModel() const;
    void Update(float timestep);
    void SetXVelocity(float velocity);
    void SetYVelocity(float velocity);
    inline my_math::vec3 GetPosition() const {
        return m_position * m_scale;
    }
private:
    float m_scale;
    my_math::vec3 m_position;
    float m_heading;
    float m_xVelocity;
    float m_yVelocity;
};
void ClearVelocity(GameObject& object);
} // namespace game
