#include "CreateShapes.h"

namespace renderer
{
    Shape CreateQuad(graphics_api::IGraphicsApi* graphicsApi, float centerX, float centerY)
    {
        static constexpr float SIZE = 1.0f;
        static constexpr float HALF_SIZE = SIZE/2;
        Vec3 bottomLeft{ .vec3={centerX-HALF_SIZE, centerY-HALF_SIZE, 0.0f}};
        Vec2 bottomLeftTextCoord{ .vec2={0.0f, 0.0f}};
        Vec3 topRight{ .vec3={centerX+HALF_SIZE, centerY+HALF_SIZE, 0.0f}};
        Vec2 topRightTextCoord = { .vec2={1.0f, 1.0f}};
        Vec3 topLeft{ .vec3={centerX-HALF_SIZE, centerY+HALF_SIZE, 0.0f}};
        Vec2 topLeftTextCoord{ .vec2={0.0f, 1.0f}};
        Vec3 bottomRight{ .vec3={centerX+HALF_SIZE, centerY-HALF_SIZE, 0.0f}};
        Vec2 bottomRightTextCoord{ .vec2={1.0f, 0.0f}};

        std::array positions = {std::move(bottomLeft),  std::move(bottomRight), std::move(topRight), std::move(topLeft)};
        std::array textureCoords = {std::move(bottomLeftTextCoord), std::move(bottomRightTextCoord), std::move(topRightTextCoord), std::move(topLeftTextCoord)};
        std::array indices = {0u,1u,2u,2u,3u,0u};

        Shape quadBuffer{graphicsApi};

        quadBuffer.positionsBuffer.UploadData(positions);
        quadBuffer.textureCoordinatesBuffer.UploadData(textureCoords);
        quadBuffer.indexBuffer.UploadData(indices);

        return quadBuffer;
    }
} // namespace renderer
