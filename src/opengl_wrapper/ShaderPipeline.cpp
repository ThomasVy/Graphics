#include "ShaderPipeline.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Config.h"
#include "logger/Log.h"
namespace
{
    constexpr std::string_view VERTEX_SHADER_PATH = BIN_LOCATION "/shaders/shader.vert";
    constexpr std::string_view FRAGMENT_SHADER_PATH = BIN_LOCATION "/shaders/shader.frag";
}

class ShaderPipeline::Impl
{
public:
    Impl(IFilesystem* filesystem)
    : m_shaderProgram(std::make_unique<ShaderProgram>())
    , m_vertexShader(std::make_unique<Shader>(filesystem, VERTEX_SHADER_PATH.data(), GL_VERTEX_SHADER))
    , m_fragmentShader(std::make_unique<Shader>(filesystem, FRAGMENT_SHADER_PATH.data(), GL_FRAGMENT_SHADER))
    {
        m_shaderProgram->AttachShader(*m_vertexShader);
        m_shaderProgram->AttachShader(*m_fragmentShader);
        m_shaderProgram->SetActive();
    }

    void Recompile()
    {
        m_vertexShader->Recompile();
        m_fragmentShader->Recompile();
        m_shaderProgram->SetActive();
    }

    void SetUniform(std::string_view uniformName, const my_math::vec4 &value)
    {
        m_shaderProgram->SetUniform(uniformName, value);
    }
private:
    std::unique_ptr<ShaderProgram> m_shaderProgram;
    std::unique_ptr<Shader> m_vertexShader;
    std::unique_ptr<Shader> m_fragmentShader;
};


ShaderPipeline::ShaderPipeline( IFilesystem* filesystem)
: m_impl{new Impl(filesystem), [](Impl * impl){delete impl;}}
{
}

void ShaderPipeline::Recompile()
{
    m_impl->Recompile();
}

void ShaderPipeline::SetUniform(std::string_view uniformName, const my_math::vec4 &value)
{
    m_impl->SetUniform(uniformName, value);
}
