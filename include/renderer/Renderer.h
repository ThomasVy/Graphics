#pragma once
#include "VertexBuffer.h"
#include "ShaderPipeline.h"
#include "graphics_api/IGraphicsApi.h"
#include <vector>
#include "IEntity.h"

namespace renderer
{
class Renderer 
{
public:
    Renderer(graphics_api::IGraphicsApi* graphicsApi, renderer::ShaderPipeline* shaderPipeline);
    void Clear() const;

    void DrawEntity(const renderer::IEntity& object);
    void DrawEntities(const std::vector<renderer::IEntity*>& entities);

private:
    graphics_api::IGraphicsApi* m_graphicsApi;
    renderer::ShaderPipeline* m_shaderPipeline;
    VertexBuffer<Matrix> m_modelsBuffer;
};
}