#include "ShaderProgram.h"
#include "logger/Log.h"
#include <stdexcept>
#include <vector>
void ActivateShaderProgram(const ShaderProgram& shaderProgram)
{
    auto linkSucceed = shaderProgram.Link();
    if (!linkSucceed)
        throw std::runtime_error("Shader program failed to link");
    shaderProgram.UseProgram();
}

void ShaderProgram::UseProgram() const
{
	GLCALL(glUseProgram(m_program));
}

void ShaderProgram::Attach(GLuint shaderId) const
{
	GLCALL(glAttachShader(m_program, shaderId));
}

bool ShaderProgram::Link() const
{
    GLCALL(glLinkProgram(m_program));
    GLCALL(glValidateProgram(m_program));
    GLint success;
	GLCALL(glGetProgramiv(m_program, GL_LINK_STATUS, &success));
	if (!success) {
		GLint logLength;
		GLCALL(glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength));
		std::vector<char> log(logLength);
		GLCALL(glGetProgramInfoLog(m_program, logLength, NULL, log.data()));

		logger::Error("SHADER_PROGRAM linking {}\n", log.data());
		return false;
	}
    logger::Info("SHADER_PROGRAM successfully compiled and linked");
    return true;
}