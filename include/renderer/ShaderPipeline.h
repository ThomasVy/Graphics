#pragma once
#include <memory>
#include "math/MatrixAndVectorMath.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "graphics_api/IGraphicsApi.h"

class ShaderPipeline
{
public:
    ShaderPipeline(graphics_api::IGraphicsApi* graphicsApi );
    void Recompile();
    template <typename T>
    void SetUniform(std::string_view uniformName, const T* value, uint32_t count = 1)
    {
        m_shaderProgram->SetUniform(uniformName, value, count);
    }
private:
    std::unique_ptr<ShaderProgram> m_shaderProgram;
    std::unique_ptr<Shader> m_vertexShader;
    std::unique_ptr<Shader> m_fragmentShader;
};