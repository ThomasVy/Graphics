#include "GameObject.h"

namespace game
{
GameObject::GameObject(const renderer::Shape& shape, const Texture& texture, float scale, my_math::vec3 position, float heading)
    : m_shape(shape)
    , m_texture(texture)
    , m_scale(scale)
    , m_position(std::move(position))
    , m_heading(heading)
    , m_xVelocity(0.0f)
    , m_yVelocity(0.0f)
{
}

my_math::mat4 GameObject::GetModel() const
{
    auto model = my_math::mat4(1.0f);
    model = my_math::translate(model, m_position);
    model = my_math::scale(model, my_math::vec3(m_scale, m_scale, 1.0f)); //scale
    model = my_math::rotate(model, m_heading, my_math::vec3(0.0f, 0.0f, 1.0f));
    return model;
}

const renderer::Shape& GameObject::GetShape() const 
{
    return m_shape;
}

void GameObject::Update(float timestep)
{
    m_position.x += timestep * m_xVelocity;
    m_position.y += timestep * m_yVelocity;
    m_heading += 0.1f;
}

void GameObject::SetXVelocity(float velocity)
{
    m_xVelocity = velocity;
}

void GameObject::SetYVelocity(float velocity)
{
    m_yVelocity = velocity;
}

void ClearVelocity(GameObject& object)
{
    object.SetXVelocity(0.0f);
    object.SetYVelocity(0.0f);
}

uint32_t GameObject::GetTextureId() const 
{
    return m_texture.GetImageSlot();
}

} // namespace game
