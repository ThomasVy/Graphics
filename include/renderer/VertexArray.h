#pragma once
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer) const;
private:
    uint32_t m_rendererId;
};