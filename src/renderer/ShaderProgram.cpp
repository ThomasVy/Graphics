#include "ShaderProgram.h"
#include "logger/Log.h"
#include <stdexcept>
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
		return true;
	}
}
void ShaderProgram::LinkAndValidate() const
{
	const auto linkSucceed = Link(m_programId);
    if (!linkSucceed)
        throw std::runtime_error("Shader program failed to link");
	GLCALL(glUseProgram(m_programId));
}

void ShaderProgram::AttachShader(Shader* shader)
{
	m_shaders.push_back(shader);
	GLCALL(glAttachShader(m_programId, shader->GetShaderId()));
}

void ShaderProgram::DetachShader(Shader* shader)
{
	std::erase(m_shaders, shader);
	GLCALL(glDetachShader(m_programId, shader->GetShaderId()));
}

ShaderProgram::~ShaderProgram()
{
	GLCALL(glDeleteProgram(m_programId));
}

void ShaderProgram::Bind() const
{
	GLCALL(glUseProgram(m_programId));
}

void ShaderProgram::Unbind() const
{
	GLCALL(glUseProgram(0));
}

ShaderProgram::ShaderProgram(graphics_api::IGraphicsApi* graphicsApi)
	: m_graphicsApi(graphicsApi)
	, m_programId(glCreateProgram())
{
}

int ShaderProgram::GetUniformLocation(const std::string& uniformName)
{
	if (m_locationCache.contains(uniformName))
		return m_locationCache.at(uniformName);
	auto location = m_graphicsApi->GetUniformLocation(m_programId, uniformName);
	if(location == -1)
		logger::Warn("uniform {} does not exist", uniformName);
	m_locationCache[uniformName] = location;
	return location;
}

void ShaderProgram::Recompile()
{
	m_locationCache.clear();
	for (const auto shader : m_shaders)
	{
		shader->Recompile();
	}
	LinkAndValidate();
}

