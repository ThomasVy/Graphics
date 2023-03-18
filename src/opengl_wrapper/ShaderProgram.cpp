#include "ShaderProgram.h"
#include "logger/Log.h"
#include <stdexcept>
#include <vector>
#include "Shader.h"

namespace{
	bool Link(GLuint programId)
	{
		GLCALL(glLinkProgram(programId));
		GLCALL(glValidateProgram(programId));
		GLint success;
		GLCALL(glGetProgramiv(programId, GL_LINK_STATUS, &success));
		if (!success) {
			GLint logLength;
			GLCALL(glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength));
			std::vector<char> log(logLength);
			GLCALL(glGetProgramInfoLog(programId, logLength, NULL, log.data()));

			logger::Error("SHADER_PROGRAM linking {}\n", log.data());
			return false;
		}
		logger::Info("SHADER_PROGRAM successfully compiled and linked");
		return true;
	}
}
void ShaderProgram::SetActive() const
{
	const auto linkSucceed = Link(m_program);
    if (!linkSucceed)
        throw std::runtime_error("Shader program failed to link");
	GLCALL(glUseProgram(m_program));
}

void ShaderProgram::AttachShader(const Shader& shader) const
{
	GLCALL(glAttachShader(m_program, shader));
}

void ShaderProgram::DetachShader(const Shader& shader) const
{
	GLCALL(glDetachShader(m_program, shader));
}