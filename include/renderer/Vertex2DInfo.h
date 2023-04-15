#pragma once
#include <array>
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/BufferInfo.h"
#include "Texture.h"


namespace renderer
{
    struct Vertex2DInfo
    {
        my_math::vec3 positions;
        my_math::vec2 textureCoordinates;
        float textureId;
        my_math::mat4 model;

        static constexpr auto GetLayout()
        {
            return std::array{
                graphics_api::BufferInfo{
                    .offset = offsetof(Vertex2DInfo, positions),
                    .count = 3,
                    .divisor=0,
                    .type = graphics_api::DataType::Float,
                    .normalized = false},
                graphics_api::BufferInfo{
                    .offset = offsetof(Vertex2DInfo, textureCoordinates),
                    .count = 2,
                    .divisor=0,
                    .type = graphics_api::DataType::Float,
                    .normalized = false},
                graphics_api::BufferInfo{
                    .offset = offsetof(Vertex2DInfo, textureId),
                    .count =1,
                    .divisor=0,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                },
                graphics_api::BufferInfo{
                    .offset = offsetof(Vertex2DInfo, model),
                    .count =4,
                    .divisor=0,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                },
                graphics_api::BufferInfo{
                    .offset = offsetof(Vertex2DInfo, model) + sizeof(my_math::vec4),
                    .count =4,
                    .divisor=0,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                },
                graphics_api::BufferInfo{
                    .offset = offsetof(Vertex2DInfo, model) + 2*sizeof(my_math::vec4),
                    .count =4,
                    .divisor=0,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                },
                graphics_api::BufferInfo{
                    .offset = offsetof(Vertex2DInfo, model) + 3*sizeof(my_math::vec4),
                    .count =4,
                    .divisor=0,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                }
            };
        }
    };
    namespace instancing
    {
        struct Vertex2DInfo
        {
            my_math::vec2 positions;
            my_math::vec2 textureCoordinates;

            static constexpr auto GetLayout()
            {
                return std::array{
                    graphics_api::BufferInfo{
                        .offset = offsetof(Vertex2DInfo, positions),
                        .count = 2,
                        .divisor=0,
                        .type = graphics_api::DataType::Float,
                        .normalized = false},
                    graphics_api::BufferInfo{
                        .offset = offsetof(Vertex2DInfo, textureCoordinates),
                        .count = 2,
                        .divisor=0,
                        .type = graphics_api::DataType::Float,
                        .normalized = false}
                };
            }
        };

        struct Texture
        {
            float textureId;
            static constexpr auto GetLayout()
            {
                return std::array{
                    graphics_api::BufferInfo{
                        .offset = offsetof(Texture, textureId),
                        .count =1,
                        .divisor=1,
                        .type = graphics_api::DataType::Float,
                        .normalized = false
                    }
                };
            }
        };

        struct Model
    {
        my_math::mat4 model;
        static constexpr auto GetLayout()
        {
            return std::array{
                graphics_api::BufferInfo{
                    .offset = offsetof(Model, model),
                    .count =4,
                    .divisor=1,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                },
                graphics_api::BufferInfo{
                    .offset = offsetof(Model, model)+sizeof(my_math::vec4),
                    .count =4,
                    .divisor=1,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                },
                graphics_api::BufferInfo{
                    .offset = offsetof(Model, model)+2*sizeof(my_math::vec4),
                    .count =4,
                    .divisor=1,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                },
                graphics_api::BufferInfo{
                    .offset = offsetof(Model, model)+3*sizeof(my_math::vec4),
                    .count =4,
                    .divisor=1,
                    .type = graphics_api::DataType::Float,
                    .normalized = false
                }
            };
        }
    };
    } // namespace instanced

struct Quad {
    std::array<Vertex2DInfo, 4> vertexInfo;
    std::array<uint32_t, 6> indices;
};

inline Quad CreateQuad(float x, float y, const Texture& texture)
{
    static constexpr float SIZE = 1.0f;
    static constexpr float HALF_SIZE = SIZE/2;
    Vertex2DInfo bottomLeft{.positions = {x-HALF_SIZE, y-HALF_SIZE, 0.0f}, .textureCoordinates = {0.0f, 0.0f}, .textureId = static_cast<float>(texture.GetImageSlot()), .model=my_math::mat4{1.0f}};
    Vertex2DInfo bottomRight{.positions = {x+HALF_SIZE, y-HALF_SIZE, 0.0f}, .textureCoordinates = {1.0f, 0.0f}, .textureId = static_cast<float>(texture.GetImageSlot()), .model=my_math::mat4{1.0f}};
    Vertex2DInfo topRight{ .positions = {x+HALF_SIZE, y+HALF_SIZE, 0.0f}, .textureCoordinates = {1.0f, 1.0f}, .textureId = static_cast<float>(texture.GetImageSlot()), .model=my_math::mat4{1.0f}};
    Vertex2DInfo topLeft{ .positions = {x-HALF_SIZE, y+HALF_SIZE, 0.0f}, .textureCoordinates = {0.0f, 1.0f}, .textureId = static_cast<float>(texture.GetImageSlot()), .model=my_math::mat4{1.0f}};

    return Quad{
        .vertexInfo={std::move(bottomLeft), std::move(bottomRight), std::move(topRight), std::move(topLeft)},
        .indices={ 0u,1u,2u, 2u,3u,0u }
    };
}
} // namespace renderer
