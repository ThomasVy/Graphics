#pragma once
#include <string>
#include "filesystem/IFilesystem.h"

enum class ShaderType
{
	Vertex,
	Fragment
};

class Shader
{
public:
	Shader(IFilesystem* filesystem, std::string path, ShaderType type);
	~Shader();

	void Recompile();
	uint32_t GetShaderId() const;

private:
	IFilesystem* m_filesystem;
	std::string m_path;
	uint32_t m_shaderId;
};