#include "ShaderPipeline.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Config.h"

namespace
{
    constexpr std::string_view VERTEX_SHADER_PATH = BIN_LOCATION "/shaders/shader.vert";
    constexpr std::string_view FRAGMENT_SHADER_PATH = BIN_LOCATION "/shaders/shader.frag";
}

class ShaderPipeline::Impl
{
public:
    Impl()
    : m_shaderProgram(std::make_unique<ShaderProgram>())
    , m_vertexShader(std::make_unique<Shader>(VERTEX_SHADER_PATH.data(), GL_VERTEX_SHADER, *m_shaderProgram))
    , m_fragmentShader(std::make_unique<Shader>(FRAGMENT_SHADER_PATH.data(), GL_FRAGMENT_SHADER, *m_shaderProgram))
    {
        ActivateShaderProgram(*m_shaderProgram);
    }
    void Recompile()
    {
        m_shaderProgram = std::make_unique<ShaderProgram>();
        m_vertexShader = std::make_unique<Shader>(VERTEX_SHADER_PATH.data(), GL_VERTEX_SHADER, *m_shaderProgram);
        m_fragmentShader = std::make_unique<Shader>(FRAGMENT_SHADER_PATH.data(), GL_FRAGMENT_SHADER, *m_shaderProgram);
        ActivateShaderProgram(*m_shaderProgram);
    }
private:
    std::unique_ptr<ShaderProgram> m_shaderProgram;
    std::unique_ptr<Shader> m_vertexShader;
    std::unique_ptr<Shader> m_fragmentShader;
};


ShaderPipeline::ShaderPipeline()
: m_impl{new Impl, [](Impl * impl){delete impl;}}
{
}

void ShaderPipeline::Recompile()
{
    m_impl->Recompile();
}
