#pragma once

#include "GLHandle.h"
#include <string>
#include "GLDebug.h"
#include "math/MatrixAndVectorMath.h"

class Shader;

class ShaderProgram {
public:
	void SetActive() const;
    void AttachShader(const Shader& shader) const;
    void DetachShader(const Shader& shader) const;

    void SetUniform(std::string_view uniformName, const my_math::vec4& value);
private:
	ShaderProgramHandle m_program;
};