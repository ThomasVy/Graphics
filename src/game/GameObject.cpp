#include "GameObject.h"

namespace game
{
GameObject::GameObject(const renderer::Shape& shape,  const renderer::SubTexture* texture, float scale, my_math::vec3 position, float heading)
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
    model = my_math::rotate(model, m_heading, my_math::vec3(0.0f, 0.0f, 1.0f));
    model = my_math::scale(model, my_math::vec3(m_scale, m_scale, 1.0f)); //scale
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
}

void GameObject::SetXVelocity(float velocity)
{
    m_xVelocity = velocity;
}

void GameObject::SetYVelocity(float velocity)
{
    m_yVelocity = velocity;
}

uint32_t GameObject::GetTextureId() const  
{
    if (!m_texture)
        return -1;
    return m_texture->GetTextureId();
}

std::vector<renderer::Vec2> GameObject::TextureCoords() const 
{
    std::vector<renderer::Vec2> textCoords;
    if (!m_texture) return textCoords;
    auto originalCoords = m_texture->GetCoords();
    if (m_xVelocity < 0)
    {
        auto temp = originalCoords.bottomLeft;
        originalCoords.bottomLeft = originalCoords.bottomRight;
        originalCoords.bottomRight = temp;
        temp = originalCoords.topLeft;
        originalCoords.topLeft = originalCoords.topRight;
        originalCoords.topRight = temp;
    }

    // if (m_yVelocity < 0)
    // {
    //     auto temp = originalCoords.bottomLeft;
    //     originalCoords.bottomLeft = originalCoords.topLeft;
    //     originalCoords.topLeft = temp;
    //     temp = originalCoords.bottomRight;
    //     originalCoords.bottomRight = originalCoords.topRight;
    //     originalCoords.topRight = temp;
    // }
    textCoords.reserve(4);
    textCoords.emplace_back(originalCoords.bottomLeft);
    textCoords.emplace_back(originalCoords.bottomRight);
    textCoords.emplace_back(originalCoords.topRight);
    textCoords.emplace_back(originalCoords.topLeft);
    return textCoords;
}

void ClearVelocity(GameObject& object)
{
    object.SetXVelocity(0.0f);
    object.SetYVelocity(0.0f);
}

void GameObject::SetTexture(const renderer::SubTexture* texture)
{
    m_texture = texture;
}


} // namespace game
