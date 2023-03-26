#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderPipeline.h"
#include "graphics_api/IGraphicsApi.h"

class Renderer 
{
public:
    Renderer(graphics_api::IGraphicsApi* graphicsApi);
    void Clear() const;
    void Draw(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer, const ShaderPipeline& shaderPipeline) const;
private:
    graphics_api::IGraphicsApi* m_graphicsApi;
};