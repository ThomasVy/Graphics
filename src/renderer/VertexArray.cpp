#include "VertexArray.h"
#include "graphics_api/opengl_wrapper/GLDebug.h"

VertexArray::VertexArray()
    : m_rendererId{}
{
    GLCALL(glGenVertexArrays(1, &m_rendererId));
}

VertexArray::~VertexArray()
{
    GLCALL(GLCALL(glDeleteVertexArrays(1, &m_rendererId)));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer) const
{
    GLCALL(glBindVertexArray(m_rendererId));
    //vb.Bind();
    //indexBuffer.Bind();
    const auto &elements = layout.GetElements();
    uint64_t offset = 0;
    for (auto i = 0u; i < elements.size(); ++i)
    {
        const auto &element = elements[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *)offset));
        offset += element.count * element.typeSize;
    }
}