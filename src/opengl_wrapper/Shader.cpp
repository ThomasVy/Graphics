#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include "logger/Log.h"
#include "ShaderProgram.h"
#include <vector>

namespace
{
    std::string ReadShader(std::string_view filePath)
    {
        try {
            std::ifstream file;
            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            file.open(filePath.data());
            std::stringstream sourceStream;
            sourceStream << file.rdbuf();
            file.close();
            return sourceStream.str();
        }
        catch (std::ifstream::failure &) {
            logger::Error("SHADER failure reading {}", filePath);
        }
        throw std::runtime_error("Could not read shader");
    }

    bool CompileShader(const char * shaderSource, GLenum type, const ShaderHandle& shaderHandle) {

        // compile shader
        GLCALL(glShaderSource(shaderHandle, 1, &shaderSource, NULL));
        GLCALL(glCompileShader(shaderHandle));

        // check for errors
        GLint success;
        GLCALL(glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success));

        if (!success) {
            GLint logLength;
            GLCALL(glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength));
            std::vector<char> log(logLength);
            GLCALL(glGetShaderInfoLog(shaderHandle, logLength, NULL, log.data()));

            logger::Error("SHADER compiling Failed:\n{}", log.data());
        }
        return success;
    }
}
Shader::Shader(std::string path, GLenum type, const ShaderProgram& shaderProgram)
	: m_type(type)
	, m_path(std::move(path))
{
    try
    {
        ShaderHandle shaderHandle{m_type};
        auto shaderSource = ReadShader(m_path);
        CompileShader(shaderSource.c_str(), m_type, shaderHandle);
        shaderProgram.Attach(shaderHandle);
    }
    catch(std::exception&)
    {
        throw std::runtime_error("Shader did not compile");
    }
}