#pragma once

#include "GLHandle.h"
#include <string>
#include "GLDebug.h"

class Shader;

class ShaderProgram {
public:
	void SetActive() const;
    void AttachShader(const Shader& shader) const;
    void DetachShader(const Shader& shader) const;
private:
	ShaderProgramHandle m_program;
};