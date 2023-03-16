#include "GLHandle.h"
#include <algorithm>

GLHandle::GLHandle(GLuint id)
: m_id{id}
{}

GLHandle::GLHandle(GLHandle&& other) noexcept
    : m_id(std::move(other.m_id))
{
	other.m_id = 0;
}

GLHandle& GLHandle::operator=(GLHandle&& other) noexcept
{
    std::swap(m_id, other.m_id);
	return *this;
}

GLHandle::operator GLuint() const
{
    return m_id;
}

GLuint GLHandle::value() const
{
    return m_id;
}


ShaderHandle::ShaderHandle(GLenum type)
: GLHandle(glCreateShader(type))
{}
ShaderHandle::~ShaderHandle()
{
    GLCALL(glDeleteShader(m_id));
}

ShaderProgramHandle::ShaderProgramHandle()
: GLHandle(glCreateProgram())
{}
ShaderProgramHandle::~ShaderProgramHandle()
{
    GLCALL(glDeleteProgram(m_id));
}

VertexArrayHandle::VertexArrayHandle()
: GLHandle(0)
{
    GLCALL(glGenVertexArrays(1, &m_id));
}
VertexArrayHandle::~VertexArrayHandle()
{
    GLCALL(glDeleteVertexArrays(1, &m_id));
}


VertexBufferHandle::VertexBufferHandle()
: GLHandle(0)
{
    GLCALL(glGenBuffers(1, &m_id));
}
VertexBufferHandle::~VertexBufferHandle()
{
    GLCALL(glDeleteBuffers(1, &m_id));
}

TextureHandle::TextureHandle()
: GLHandle(0)
{
    GLCALL(glGenTextures(1, &m_id));
}
TextureHandle::~TextureHandle()
{
    GLCALL(glDeleteTextures(1, &m_id));
}
