#pragma once
#include <cstdint> 
#include <vector>
#include <gl/glew.h>
#include <stdexcept>

struct VertexBufferElements // probably should use my own types and convert it later
{
    int32_t count;
    uint32_t typeSize;
    uint32_t  type; 
    uint8_t normalized;
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElements> m_elements;
    uint32_t m_stride{0};

public:
    template<typename T> 
    void Push(uint32_t count)
    {
        std::runtime_error("Generic version should not be called");
    }

    template<> 
    void Push<float>(uint32_t count)
    {
        auto typeSize = static_cast<uint32_t>(sizeof(float));
        m_elements.emplace_back(count, typeSize, GL_FLOAT, GL_FALSE);
        m_stride += count * typeSize;
    }

    template<> 
    void Push<uint32_t>(uint32_t count)
    {
        auto typeSize = static_cast<uint32_t>(sizeof(uint32_t));
        m_elements.emplace_back(count, typeSize, GL_UNSIGNED_INT, GL_FALSE);
        m_stride += count * typeSize;
    }

    template<> 
    void Push<uint8_t>(uint32_t count)
    {
        auto typeSize = static_cast<uint32_t>(sizeof(uint8_t));
        m_elements.emplace_back(count, typeSize, GL_UNSIGNED_BYTE, GL_TRUE);
        m_stride += count * typeSize;
    }

    uint32_t GetStride() const { return m_stride; }
    const std::vector<VertexBufferElements>& GetElements() const { return m_elements; }
};