#include "ShaderProgram.h"
#include "logger/Log.h"
#include <stdexcept>
#include "Shader.h"

void ShaderProgram::AttachShader(Shader* shader)
{
	m_shaders.push_back(shader);
}

ShaderProgram::~ShaderProgram()
{
	m_graphicsApi->DeleteShaderProgram(m_programId);
}

ShaderProgram::ShaderProgram(graphics_api::IGraphicsApi* graphicsApi)
	: m_graphicsApi(graphicsApi)
	, m_programId(m_graphicsApi->CreateShaderProgram())
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
	std::vector<uint32_t> shaderIds;
	shaderIds.reserve(m_shaders.size());
	for (auto* shader : m_shaders)
	{
		shader->Recompile();
		shaderIds.push_back(shader->GetShaderId());
	}
	m_graphicsApi->LinkShaders(m_programId, shaderIds);
}

