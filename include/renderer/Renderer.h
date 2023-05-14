#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderPipeline.h"
#include "graphics_api/IGraphicsApi.h"
#include "Instance.h"

class Renderer 
{
public:
    Renderer(graphics_api::IGraphicsApi* graphicsApi);
    void Clear() const;

    template<typename T>
    void Draw(const VertexBuffer<T>& vertexBuffer, const IndexBuffer& indexBuffer) const
    {
        vertexBuffer.Bind(0);
        m_graphicsApi->Draw(indexBuffer.GetId(), indexBuffer.GetCount());
    }

    void DrawInstance(const renderer::Instance& instance) const
    {
        instance.Bind();
        m_graphicsApi->DrawInstanced(instance.GetIndexBufferId(), instance.GetIndicesCount(), instance.GetInstanceCount());
    }
private:
    graphics_api::IGraphicsApi* m_graphicsApi;
};