#include "SubTexture.h"

namespace renderer
{
SubTexture::SubTexture(const Texture& texture, my_math::vec2 index)
    : m_mainTexture(texture)
    , m_indexInMainTexture(std::move(index))
{
}

SubTexture::Coordinates SubTexture::GetCoords() const
{
    const auto& eachSpriteSize = m_mainTexture.GetSpriteSize();
    return SubTexture::Coordinates{
        .bottomLeft = {(m_indexInMainTexture.x * eachSpriteSize.x)/m_mainTexture.GetWidth(), (m_indexInMainTexture.y * eachSpriteSize.y)/m_mainTexture.GetHeight()},
        .bottomRight = {((m_indexInMainTexture.x + 1) * eachSpriteSize.x)/m_mainTexture.GetWidth(), (m_indexInMainTexture.y * eachSpriteSize.y)/m_mainTexture.GetHeight()},
        .topLeft = {((m_indexInMainTexture.x) * eachSpriteSize.x)/m_mainTexture.GetWidth(), ((m_indexInMainTexture.y+1)* eachSpriteSize.y)/m_mainTexture.GetHeight()},
        .topRight = {((m_indexInMainTexture.x+1) * eachSpriteSize.x)/m_mainTexture.GetWidth(), ((m_indexInMainTexture.y+1)* eachSpriteSize.y)/m_mainTexture.GetHeight()}
    };
}

uint32_t SubTexture::GetTextureId() const
{
    return m_mainTexture.GetImageSlot();
}  
} // namespace renderer
