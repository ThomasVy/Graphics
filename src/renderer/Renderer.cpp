#include "Renderer.h"

Renderer::Renderer(graphics_api::IGraphicsApi* graphicsApi)
    : m_graphicsApi{graphicsApi}
{
}


void Renderer::Draw(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer, const ShaderPipeline& shaderPipeline) const
{
    m_graphicsApi->Draw(vertexBuffer.GetId(), indexBuffer.GetId(), indexBuffer.GetCount());
}

void Renderer::Clear() const
{
    m_graphicsApi->Clear();
}
