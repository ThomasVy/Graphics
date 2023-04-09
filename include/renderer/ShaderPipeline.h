#pragma once
#include <memory>
#include "math/MatrixAndVectorMath.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "graphics_api/IGraphicsApi.h"
#include "Texture.h"
namespace renderer
{
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

void SetTextures(ShaderPipeline& pipeline, std::span<Texture> textures)
{
    std::vector<uint32_t> samplers;
    samplers.reserve(textures.size());
    for (const auto& texture : textures)
    {
        texture.Bind();
        samplers.push_back(texture.GetImageSlot());
    }
    pipeline.SetUniform("u_texture", samplers.data(), static_cast<uint32_t>(samplers.size()) );
}
}