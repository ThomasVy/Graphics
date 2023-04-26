#pragma once
#include "VertexBuffer.h"
#include "Vertex2DInfo.h"
#include <span>
#include "IndexBuffer.h"

namespace renderer
{
class Instance
{
public:
    Instance(graphics_api::IGraphicsApi* graphicsApi);

    void SetTexturesIds(std::span<instancing::Vec1> data);
    void SetModels(std::span<instancing::Matrix> data);
    void SetPositions(std::span<instancing::Vec3> data);
    void SetTextureCoordinates(std::span<instancing::Vec2> data);
    void SetIndices(std::span<uint32_t> data);

    uint32_t GetIndicesCount() const;
    uint32_t GetInstanceCount() const;
    uint32_t GetIndexBufferId() const;
    void Bind() const;
private:
    IndexBuffer m_indexBuffer;
    VertexBuffer<instancing::Vec3> m_positionsBuffer;
    VertexBuffer<instancing::Vec2> m_textureCoordinatesBuffer;
    VertexBuffer<instancing::Vec1> m_textureIdBuffer;
    VertexBuffer<instancing::Matrix> m_modelsBuffer;
};
} // namespace renderer
