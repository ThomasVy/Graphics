#include "GameObject.h"

namespace game
{
GameObject::GameObject(float scale, my_math::vec3 position, float heading)
    : m_scale(scale)
    , m_position(std::move(position))
    , m_heading(heading)
{
}

my_math::mat4 GameObject::GetModel() const
{
    auto model = my_math::mat4(1.0f);
    model = my_math::scale(model, my_math::vec3(m_scale, m_scale, 1.0f)); //scale
    model = my_math::rotate(model, m_heading, my_math::vec3(0.0f, 0.0f, 1.0f));
    model = my_math::translate(model, m_position);
    return model;
}

void GameObject::Update(window_context::Timestep timestep)
{
    
}


} // namespace game
