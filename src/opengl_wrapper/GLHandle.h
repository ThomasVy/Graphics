#pragma once
#include "GLDebug.h"

class GLHandle{
public:
	GLHandle(GLuint id);
	// Disallow copying
	GLHandle(const GLHandle&) = delete;
    GLHandle& operator=(const GLHandle&) = delete;
	// Allow moving
	GLHandle(GLHandle&& other) noexcept;
	GLHandle& operator=(GLHandle&& other) noexcept;
	// Clean up after ourselves.
	virtual ~GLHandle() = default;

    operator GLuint() const;
	GLuint value() const;

protected:
    GLuint m_id;
};

class ShaderHandle : public GLHandle{
public:
	ShaderHandle(GLenum type);
    ~ShaderHandle();
};

class ShaderProgramHandle : public GLHandle{

public:
	ShaderProgramHandle();
    ~ShaderProgramHandle();
};


class VertexArrayHandle : public GLHandle{
public:
	VertexArrayHandle();
    ~VertexArrayHandle();
};

class VertexBufferHandle : public GLHandle{

public:
	VertexBufferHandle();
    ~VertexBufferHandle();
};

class TextureHandle : public GLHandle{
public:
	TextureHandle();
    ~TextureHandle();
};