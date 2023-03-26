#include "VertexBuffer.h"
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/opengl_wrapper/GLDebug.h"
VertexBuffer::VertexBuffer(const void* data, uint32_t typeSize, size_t count)
{
    GLCALL(glGenBuffers(1, &m_bufferID));
	Bind();
    GLCALL(glBufferData(GL_ARRAY_BUFFER, count*typeSize, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
}

void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_bufferID));
}