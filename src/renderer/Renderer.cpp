#include "Renderer.h"
#include "IndexBuffer.h"
#include <memory>

namespace renderer
{

Renderer::Renderer(graphics_api::IGraphicsApi* graphicsApi, renderer::ShaderPipeline* shaderPipeline)
    : m_graphicsApi{graphicsApi}
    , m_shaderPipeline(shaderPipeline)
    , m_textureCoordinatesBuffer{graphicsApi, 1, false}
    , m_modelsBuffer(m_graphicsApi, 2, true)
{
}

void Renderer::Clear() const
{
    m_graphicsApi->Clear();
}

void Renderer::DrawEntity(const renderer::IEntity& object, bool showWireFrame)
{
    auto textureId = object.GetTextureId();
    if (textureId == -1)
    {
        logger::Error("Texture is null");
        return;
    }
    m_shaderPipeline->SetUniform("u_texId", &textureId);
    auto textCoords = object.TextureCoords();
    m_textureCoordinatesBuffer.UploadData(textCoords);
    m_textureCoordinatesBuffer.Bind();
    object.GetShape().Bind();

    auto models = std::array<Matrix, 1>{object.GetModel()};
    m_modelsBuffer.UploadData(models);
    m_modelsBuffer.Bind();
    m_graphicsApi->DrawInstanced(m_shaderPipeline->GetProgramId(), object.GetShape().indexBuffer.GetCount(), 1, showWireFrame);
}

void Renderer::DrawEntities(const std::vector<std::unique_ptr<renderer::IEntity>>& entities, bool showWireFrame)
{
    if(entities.empty())
        return;

    const auto& sampleObject = entities[0];
    auto textureId = sampleObject->GetTextureId();
    if (textureId == -1)
    {
        logger::Error("Texture is null");
        return;
    }
    m_shaderPipeline->SetUniform("u_texId", &textureId);
    sampleObject->GetShape().Bind();

    auto models = std::vector<Matrix>();
    models.reserve(entities.size());
    for (const auto& object : entities)
    {
        models.emplace_back(object->GetModel());
    }
    auto textCoords = sampleObject->TextureCoords();
    m_textureCoordinatesBuffer.UploadData(textCoords);
    m_textureCoordinatesBuffer.Bind();
    m_modelsBuffer.UploadData(models);
    m_modelsBuffer.Bind();
    m_graphicsApi->DrawInstanced(m_shaderPipeline->GetProgramId(), sampleObject->GetShape().indexBuffer.GetCount(), (uint32_t)entities.size(), showWireFrame);
}

void Renderer::SetViewProj(const my_math::mat4& viewProjMatrix)
{
    m_shaderPipeline->SetUniform("u_PV", &viewProjMatrix);
}

}