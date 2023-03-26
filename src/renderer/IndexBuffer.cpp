#include "IndexBuffer.h"
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/opengl_wrapper/GLDebug.h"

IndexBuffer::IndexBuffer(const uint32_t* data, size_t count)
	: m_bufferID{}
    , m_count(count)
{
    GLCALL(glGenBuffers(1, &m_bufferID));
	Bind();
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_bufferID));
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID));
}

void IndexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

uint32_t IndexBuffer::GetCount() const
{
	return static_cast<uint32_t>(m_count);
}
