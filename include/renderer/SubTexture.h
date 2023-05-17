#pragma once
#include "Texture.h"
#include "math/MatrixAndVectorMath.h"

namespace renderer
{
class SubTexture
{
public:
    SubTexture(const Texture& texture, my_math::vec2 index);

    struct Coordinates
    {
        my_math::vec2 bottomLeft;
        my_math::vec2 bottomRight;
        my_math::vec2 topLeft;
        my_math::vec2 topRight;
    };

    Coordinates GetCoords() const;
    uint32_t GetTextureId() const;
private:
    const Texture& m_mainTexture;
    my_math::vec2 m_indexInMainTexture;
};
} // namespace renderer