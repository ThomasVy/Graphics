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

ShaderPipeline::ShaderPipeline( IFilesystem* filesystem, graphics_api::IGraphicsApi* graphicsApi )
    : m_shaderProgram(std::make_unique<ShaderProgram>(graphicsApi))
    , m_vertexShader(std::make_unique<Shader>(filesystem, VERTEX_SHADER_PATH.data(), ShaderType::Vertex))
    , m_fragmentShader(std::make_unique<Shader>(filesystem, FRAGMENT_SHADER_PATH.data(), ShaderType::Fragment))
{
    m_shaderProgram->AttachShader(m_vertexShader.get());
    m_shaderProgram->AttachShader(m_fragmentShader.get());
    m_shaderProgram->LinkAndValidate();
}

void ShaderPipeline::Recompile()
{
    m_shaderProgram->Recompile();
}

void ShaderPipeline::Bind() const
{
    m_shaderProgram->Bind();
}

void ShaderPipeline::Unbind() const
{
    m_shaderProgram->Unbind();
}