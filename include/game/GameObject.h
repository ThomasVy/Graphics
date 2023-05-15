#pragma once
#include "renderer/IEntity.h"
#include "renderer/Texture.h"

namespace game
{
class GameObject : public renderer::IEntity
{
public:
    GameObject(const renderer::Shape& shape, const Texture& texture, float scale, my_math::vec3 position, float heading);
    void Update(float timestep);
    void SetXVelocity(float velocity);
    void SetYVelocity(float velocity);
    inline my_math::vec3 GetPosition() const {
        return m_position * m_scale;
    }
    my_math::mat4 GetModel() const override;
    const renderer::Shape& GetShape() const override;
    uint32_t GetTextureId() const override;
private:
    const renderer::Shape& m_shape;
    const Texture& m_texture;
    float m_scale;
    my_math::vec3 m_position;
    float m_heading;
    float m_xVelocity;
    float m_yVelocity;
};
void ClearVelocity(GameObject& object);

} // namespace game
