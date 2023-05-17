#pragma once
#include <vector>
#include <array>
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/BufferInfo.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "logger/Log.h"

namespace renderer
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

    struct Shape
    {
        VertexBuffer<Vec3> positionsBuffer;
        IndexBuffer indexBuffer;

        Shape(graphics_api::IGraphicsApi* graphicsApi)
        : positionsBuffer{graphicsApi, 0, false}
        , indexBuffer{graphicsApi}
        {}

        void Bind() const
        {
            positionsBuffer.Bind();
            indexBuffer.Bind();
        }
    };
} // namespace renderer
