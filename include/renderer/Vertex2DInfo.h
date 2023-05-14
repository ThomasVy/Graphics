#pragma once
#include <array>
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/BufferInfo.h"
#include "Texture.h"


namespace renderer
{
    namespace instancing
    {
        struct Vec3
        {
            my_math::vec3 vec3;
            static constexpr auto GetLayout()
            {
                return std::array{
                    graphics_api::BufferInfo{
                        .offset = offsetof(Vec3, vec3),
                        .count =3,
                        .type = graphics_api::DataType::Float,
                        .normalized = false}
                };
            }
        };

        struct Vec2
        {
            my_math::vec2 vec2;

            static constexpr auto GetLayout()
            {
                return std::array{ 
                    graphics_api::BufferInfo{
                    .offset = offsetof(Vec2, vec2),
                    .count =2,
                    .type = graphics_api::DataType::Float,
                    .normalized = false}
                };
            }
        };

        struct UInt
        {
            uint32_t integer;
            static constexpr auto GetLayout()
            {
                return std::array{
                    graphics_api::BufferInfo{
                        .offset = offsetof(UInt, integer),
                        .count =1,
                        .type = graphics_api::DataType::UInt32,
                        .normalized = false
                    }
                };
            }
        };

        struct Matrix
        {
            my_math::mat4 matrix;
            static constexpr auto GetLayout()
            {
                return std::array{
                    graphics_api::BufferInfo{
                        .offset = offsetof(Matrix, matrix),
                        .count =4,
                        .type = graphics_api::DataType::Float,
                        .normalized = false
                    },
                    graphics_api::BufferInfo{
                        .offset = offsetof(Matrix, matrix)+sizeof(my_math::vec4),
                        .count =4,
                        .type = graphics_api::DataType::Float,
                        .normalized = false
                    },
                    graphics_api::BufferInfo{
                        .offset = offsetof(Matrix, matrix)+2*sizeof(my_math::vec4),
                        .count =4,
                        .type = graphics_api::DataType::Float,
                        .normalized = false
                    },
                    graphics_api::BufferInfo{
                        .offset = offsetof(Matrix, matrix)+3*sizeof(my_math::vec4),
                        .count =4,
                        .type = graphics_api::DataType::Float,
                        .normalized = false
                    }
                };
            }
        };

        struct InstanceQuad
        {
            std::array<Vec3, 4> positions;
            std::array<Vec2, 4> textureCoords;
            std::array<uint32_t, 6> indices;
        };

        inline InstanceQuad CreateQuad(float x, float y)
        {
            static constexpr float SIZE = 1.0f;
            static constexpr float HALF_SIZE = SIZE/2;
            Vec3 bottomLeft{ .vec3={x-HALF_SIZE, y-HALF_SIZE, 0.0f}};
            Vec2 bottomLeftTextCoord{ .vec2={0.0f, 0.0f}};
            Vec3 topRight{ .vec3={x+HALF_SIZE, y+HALF_SIZE, 0.0f}};
            Vec2 topRightTextCoord = { .vec2={1.0f, 1.0f}};
            Vec3 topLeft{ .vec3={x-HALF_SIZE, y+HALF_SIZE, 0.0f}};
            Vec2 topLeftTextCoord{ .vec2={0.0f, 1.0f}};
            Vec3 bottomRight{ .vec3={x+HALF_SIZE, y-HALF_SIZE, 0.0f}};
            Vec2 bottomRightTextCoord{ .vec2={1.0f, 0.0f}};

            return InstanceQuad{
                .positions={std::move(bottomLeft),  std::move(bottomRight), std::move(topRight), std::move(topLeft)},
                .textureCoords={std::move(bottomLeftTextCoord), std::move(bottomRightTextCoord), std::move(topRightTextCoord), std::move(topLeftTextCoord)},
                .indices={0u,1u,2u,2u,3u,0u}
            };
        }

    } // namespace instanced
} // namespace renderer
