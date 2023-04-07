#include "Shader.h"
#include "logger/Log.h"

Shader::Shader(graphics_api::IGraphicsApi* graphicsApi, graphics_api::IGraphicsApi::ShaderType type)
    : m_graphicsApi(graphicsApi)
    , m_shaderId(m_graphicsApi->GenerateShader(type))
    , m_type(type)
{
}

Shader::~Shader()
{
    m_graphicsApi->DeleteShader(m_shaderId);
}

void Shader::Recompile()
{
    auto sourceContent = m_graphicsApi->ReadShaderSourceFile(m_type);
    if(sourceContent.has_value())
    {
        m_graphicsApi->CompileShader(m_shaderId, sourceContent.value());
    }
}

uint32_t Shader::GetShaderId() const
{
    return m_shaderId;
}
