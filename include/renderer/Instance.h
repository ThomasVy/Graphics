#pragma once
#include "VertexBuffer.h"
#include "Vertex2DInfo.h"
#include <span>
#include "IndexBuffer.h"
#include "ShaderPipeline.h"

namespace renderer
{
class Instance
{
public:
    Instance(graphics_api::IGraphicsApi* graphicsApi, ShaderPipeline* pipeline);

    void SetTextureId(uint32_t textureId);
    void SetModels(std::span<instancing::Matrix> data);
    void SetPositions(std::span<instancing::Vec3> data);
    void SetTextureCoordinates(std::span<instancing::Vec2> data);
    void SetIndices(std::span<uint32_t> data);

    uint32_t GetIndicesCount() const;
    uint32_t GetInstanceCount() const;
    uint32_t GetIndexBufferId() const;
    void Bind() const;
private:
    ShaderPipeline* m_pipeline;
    IndexBuffer m_indexBuffer;
    VertexBuffer<instancing::Vec3> m_positionsBuffer;
    VertexBuffer<instancing::Vec2> m_textureCoordinatesBuffer;
    VertexBuffer<instancing::Matrix> m_modelsBuffer;
    uint32_t m_textureId;
};
} // namespace renderer
