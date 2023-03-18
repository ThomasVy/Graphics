#include "Shader.h"
#include <string>
#include <vector>
#include "logger/Log.h"

namespace
{
    bool CompileShader(const char * shaderSource, GLuint shaderId) {

        // compile shader
        GLCALL(glShaderSource(shaderId, 1, &shaderSource, NULL));
        GLCALL(glCompileShader(shaderId));

        // check for errors
        GLint success;
        GLCALL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));

        if (!success) {
            GLint logLength;
            GLCALL(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength));
            std::vector<char> log(logLength);
            GLCALL(glGetShaderInfoLog(shaderId, logLength, NULL, log.data()));

            logger::Error("SHADER compiling Failed:\n{}", log.data());
        }
        return success;
    }
}
Shader::Shader(IFilesystem* filesystem, std::string path, GLenum type)
    : m_filesystem(filesystem)
    , m_type(type)
	, m_path(std::move(path))
    , m_handle(m_type)
{
    Recompile();
}

void Shader::Recompile()
{
    try
    {
        auto shaderSource = m_filesystem->ReadFile(m_path);
        CompileShader(shaderSource.c_str(), m_handle);
    }
    catch(std::exception&)
    {
        throw std::runtime_error("Shader did not compile");
    }
}

Shader::operator GLuint() const
{
    return m_handle;
}
