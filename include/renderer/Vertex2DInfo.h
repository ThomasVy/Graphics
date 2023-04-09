#pragma once
#include <array>
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/BufferInfo.h"
#include "Texture.h"

namespace renderer
{
struct Vertex2DInfo
{
    my_math::vec2 positions;
    my_math::vec2 textureCoordinates;
    float textureId;

    static constexpr auto GetLayout()
    {
        return std::array{
            graphics_api::BufferInfo{
                .offset = offsetof(Vertex2DInfo, positions),
                .count = 2,
                .type = graphics_api::DataType::Float,
                .normalized = false},
            graphics_api::BufferInfo{
                .offset = offsetof(Vertex2DInfo, textureCoordinates),
                .count = 2,
                .type = graphics_api::DataType::Float,
                .normalized = false},
            graphics_api::BufferInfo{
                .offset = offsetof(Vertex2DInfo, textureId),
                .count = 1,
                .type = graphics_api::DataType::Float,
                .normalized = false}};
    }
};

struct Quad {
    std::array<Vertex2DInfo, 4> vertexInfo;
    std::array<uint32_t, 6> indices;
};

inline Quad CreateQuad(float x, float y, const Texture& texture)
{
    static constexpr float SIZE = 1.0f;
    static constexpr float HALF_SIZE = SIZE/2;
    Vertex2DInfo bottomLeft{.positions = {x-HALF_SIZE, y-HALF_SIZE}, .textureCoordinates = {0.0f, 0.0f}, .textureId = static_cast<float>(texture.GetImageSlot())};
    Vertex2DInfo bottomRight{.positions = {x+HALF_SIZE, y-HALF_SIZE}, .textureCoordinates = {1.0f, 0.0f}, .textureId = static_cast<float>(texture.GetImageSlot())};
    Vertex2DInfo topRight{.positions = {x+HALF_SIZE, y+HALF_SIZE}, .textureCoordinates = {1.0f, 1.0f}, .textureId = static_cast<float>(texture.GetImageSlot())};
    Vertex2DInfo topLeft{.positions = {x-HALF_SIZE, y+HALF_SIZE}, .textureCoordinates = {0.0f, 1.0f}, .textureId = static_cast<float>(texture.GetImageSlot())};

    return Quad{
        .vertexInfo={std::move(bottomLeft), std::move(bottomRight), std::move(topRight), std::move(topLeft)},
        .indices={ 0u,1u,2u, 2u,3u,0u }
    };
}
} // namespace renderer
