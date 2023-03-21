#pragma once
#include <string>
#include "GLDebug.h"
#include "GLHandle.h"
#include "filesystem/IFilesystem.h"

class Shader
{
public:
	Shader(IFilesystem* filesystem, std::string path, GLenum type);
	void Recompile();

	operator GLuint() const;
private:
	IFilesystem* m_filesystem;
	GLenum m_type;
	std::string m_path;
	ShaderHandle m_handle;
};