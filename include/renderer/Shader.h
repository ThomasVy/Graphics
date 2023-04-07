#pragma once
#include <string>
#include "filesystem/IFilesystem.h"
#include "graphics_api/IGraphicsApi.h"

class Shader
{
public:
	Shader(graphics_api::IGraphicsApi* graphicsApi, graphics_api::IGraphicsApi::ShaderType type);
	~Shader();

	void Recompile();
	uint32_t GetShaderId() const;

private:
	graphics_api::IGraphicsApi* m_graphicsApi;
	uint32_t m_shaderId;
	graphics_api::IGraphicsApi::ShaderType m_type;
};