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
    , m_vertexShader(std::make_unique<Shader>(filesystem, VERTEX_SHADER_PATH.data(), ShaderType::Vertex))
    , m_fragmentShader(std::make_unique<Shader>(filesystem, FRAGMENT_SHADER_PATH.data(), ShaderType::Fragment))
    {
        m_shaderProgram->AttachShader(m_vertexShader.get());
        m_shaderProgram->AttachShader(m_fragmentShader.get());
        m_shaderProgram->LinkAndValidate();
    }

    void Recompile()
    {
        m_shaderProgram->Recompile();
    }

    void SetUniform(std::string_view uniformName, const my_math::vec4 &value)
    {
        m_shaderProgram->SetUniform(uniformName, value);
    }

    void Bind() const
    {
        m_shaderProgram->Bind();
    }

    void Unbind() const
    {
        m_shaderProgram->Unbind();
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

void ShaderPipeline::UnBind() const
{
    m_impl->Unbind();
}

void ShaderPipeline::Bind() const
{
    m_impl->Bind();
}
