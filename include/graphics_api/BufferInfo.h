#pragma once
#include <cstddef>

namespace graphics_api
{
    enum class DataType
    {
        Float,
        UInt32
    };

    struct BufferInfo
    {
        uint64_t offset;
        uint32_t count;
        DataType type; 
        bool normalized;
    };
}