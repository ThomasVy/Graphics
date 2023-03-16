#pragma once
#include <string>
#include "GLDebug.h"

class ShaderProgram; 

class Shader
{
public:
	Shader(std::string path, GLenum type, const ShaderProgram& shaderProgram);
	std::string GetPath() const { return m_path; }
	GLenum GetType() const { return m_type; }

private:
	GLenum m_type;
	std::string m_path;
};