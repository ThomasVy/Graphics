#pragma once

#include "GLHandle.h"
#include <string>
#include "GLDebug.h"

class Shader;

class ShaderProgram {
public:
	void UseProgram() const;
    void Attach(GLuint shaderId) const;
    bool Link() const;
private:
	ShaderProgramHandle m_program;
};

void ActivateShaderProgram(const ShaderProgram& shaderProgram);