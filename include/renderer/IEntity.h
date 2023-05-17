#pragma once
#include "math/MatrixAndVectorMath.h"
#include "Shape.h"
#include "SubTexture.h"
namespace renderer
{
    class IEntity
    {
    public:
        virtual ~IEntity() = default;
        virtual my_math::mat4 GetModel() const = 0;
        virtual const Shape& GetShape() const = 0;
        virtual uint32_t GetTextureId() const = 0;
        virtual std::vector<renderer::Vec2> TextureCoords() const = 0;
    };
} // namespace renderer
