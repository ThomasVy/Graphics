#pragma once
#include <array>
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/BufferInfo.h"

struct Vertex2DInfo
{
    my_math::vec2 positions;
    my_math::vec2 textureCoordinates;

    static constexpr auto GetLayout()
    {
        return std::array{
            graphics_api::BufferInfo{
                .offset=offsetof(Vertex2DInfo, positions),
                .count=2,
                .type=graphics_api::DataType::Float,
                .normalized=false
            },
            graphics_api::BufferInfo{
                .offset=offsetof(Vertex2DInfo, textureCoordinates),
                .count=2, 
                .type=graphics_api::DataType::Float, 
                .normalized=false
            }
        };
    }
};

