#include "ShaderPipeline.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "logger/Log.h"

ShaderPipeline::ShaderPipeline(graphics_api::IGraphicsApi* graphicsApi )
    : m_shaderProgram(std::make_unique<ShaderProgram>(graphicsApi))
    , m_vertexShader(std::make_unique<Shader>(graphicsApi, graphics_api::IGraphicsApi::ShaderType::Vertex))
    , m_fragmentShader(std::make_unique<Shader>(graphicsApi, graphics_api::IGraphicsApi::ShaderType::Fragment))
{
    m_shaderProgram->AttachShader(m_vertexShader.get());
    m_shaderProgram->AttachShader(m_fragmentShader.get());
    m_shaderProgram->Recompile();
}

void ShaderPipeline::Recompile()
{
    m_shaderProgram->Recompile();
}