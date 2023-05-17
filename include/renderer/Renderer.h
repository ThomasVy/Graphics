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
    void DrawEntities(const std::vector<std::unique_ptr<renderer::IEntity>>& entities);
    void SetViewProj(const my_math::mat4& viewProjMatrix);
private:
    graphics_api::IGraphicsApi* m_graphicsApi;
    renderer::ShaderPipeline* m_shaderPipeline;
     VertexBuffer<Vec2> m_textureCoordinatesBuffer;
    VertexBuffer<Matrix> m_modelsBuffer;
};
}