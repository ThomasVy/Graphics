#include "CreateShapes.h"

namespace renderer
{
    Shape CreateQuad(graphics_api::IGraphicsApi* graphicsApi)
    {
        static constexpr float SIZE = 1.0f;
        static constexpr float HALF_SIZE = SIZE/2;
        Vec3 bottomLeft{ .vec3={-HALF_SIZE, -HALF_SIZE, 0.0f}};
        Vec3 topRight{ .vec3={HALF_SIZE, HALF_SIZE, 0.0f}};
        Vec3 topLeft{ .vec3={-HALF_SIZE, HALF_SIZE, 0.0f}};
        Vec3 bottomRight{ .vec3={HALF_SIZE, -HALF_SIZE, 0.0f}};

        std::array positions = {std::move(bottomLeft),  std::move(bottomRight), std::move(topRight), std::move(topLeft)};
        std::array indices = {0u,1u,2u,2u,3u,0u};

        Shape quadBuffer{graphicsApi};

        quadBuffer.positionsBuffer.UploadData(positions);
        quadBuffer.indexBuffer.UploadData(indices);

        return quadBuffer;
    }

    Shape CreateQuadSpriteSheet(graphics_api::IGraphicsApi* graphicsApi)
    {
        static constexpr float SIZE = 1.0f;
        static constexpr float HALF_SIZE = SIZE/2;
        Vec3 bottomLeft{ .vec3={-HALF_SIZE, -HALF_SIZE, 0.0f}};
        Vec3 topRight{ .vec3={HALF_SIZE, HALF_SIZE, 0.0f}};
        Vec3 topLeft{ .vec3={-HALF_SIZE, HALF_SIZE, 0.0f}};
        Vec3 bottomRight{ .vec3={HALF_SIZE, -HALF_SIZE, 0.0f}};

        std::array positions = {std::move(bottomLeft),  std::move(bottomRight), std::move(topRight), std::move(topLeft)};
        std::array indices = {0u,1u,2u,2u,3u,0u};

        Shape quadBuffer{graphicsApi};

        quadBuffer.positionsBuffer.UploadData(positions);
        quadBuffer.indexBuffer.UploadData(indices);

        return quadBuffer;
    }

} // namespace renderer