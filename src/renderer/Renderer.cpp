#include "Renderer.h"
#include "IndexBuffer.h"

namespace renderer
{

Renderer::Renderer(graphics_api::IGraphicsApi* graphicsApi, renderer::ShaderPipeline* shaderPipeline)
    : m_graphicsApi{graphicsApi}
    , m_shaderPipeline(shaderPipeline)
    , m_modelsBuffer(m_graphicsApi, 2, true)
{
}

void Renderer::Clear() const
{
    m_graphicsApi->Clear();
}

void Renderer::DrawEntity(const renderer::IEntity& object)
{
    auto textureId = object.GetTextureId();
    m_shaderPipeline->SetUniform("u_texId", &textureId);
    auto models = std::array<Matrix, 1>{object.GetModel()};
    m_modelsBuffer.UploadData(models);
    object.GetShape().Bind();
    m_modelsBuffer.Bind();
    m_graphicsApi->DrawInstanced(object.GetShape().indexBuffer.GetCount(), 1);
}

void Renderer::DrawEntities(const std::vector<renderer::IEntity*>& entities)
{
    if(entities.empty())
        return;

    const auto* sampleObject = entities[0];
    sampleObject->GetShape().Bind();
    auto textureId = sampleObject->GetTextureId();
    m_shaderPipeline->SetUniform("u_texId", &textureId);

    auto models = std::vector<Matrix>();
    models.reserve(entities.size());
    for (const auto* object : entities)
    {
        models.emplace_back(object->GetModel());
    }
    m_modelsBuffer.UploadData(models);
    m_modelsBuffer.Bind();
    m_graphicsApi->DrawInstanced(sampleObject->GetShape().indexBuffer.GetCount(), (uint32_t)entities.size());
}
}