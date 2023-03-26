#include "Shader.h"
#include <string>
#include <vector>
#include "logger/Log.h"
#include "graphics_api/opengl_wrapper/GLDebug.h"
#include "common/ConstExprMap.h"
namespace
{
    constexpr std::array SHADERTYPE_TO_OPENGLENUM{
        std::make_pair<ShaderType, uint32_t>(ShaderType::Fragment, GL_FRAGMENT_SHADER),
        std::make_pair<ShaderType, uint32_t>(ShaderType::Vertex, GL_VERTEX_SHADER)
    };
    
    constexpr auto ENUM_LOOKUP = ConstExprMap(SHADERTYPE_TO_OPENGLENUM);
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

Shader::Shader(IFilesystem* filesystem, std::string path, ShaderType type)
    : m_filesystem(filesystem)
	, m_path(std::move(path))
    , m_shaderId{0}
{
    auto glType = ENUM_LOOKUP.at(type);
    GLCALL(m_shaderId = glCreateShader(glType));
    Recompile();
}

Shader::~Shader()
{
    GLCALL(glDeleteShader(m_shaderId));
}

void Shader::Recompile()
{
    try
    {
        auto shaderSource = m_filesystem->ReadFile(m_path);
        CompileShader(shaderSource.c_str(), m_shaderId);
    }
    catch(std::exception&)
    {
        throw std::runtime_error("Shader did not compile");
    }
}

uint32_t Shader::GetShaderId() const
{
    return m_shaderId;
}
