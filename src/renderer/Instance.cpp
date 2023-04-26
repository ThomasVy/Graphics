#include "Instance.h"
namespace renderer
{
Instance::Instance(graphics_api::IGraphicsApi* graphicsApi)
    : m_indexBuffer(graphicsApi)
    , m_positionsBuffer(graphicsApi, 0, false)
    , m_textureCoordinatesBuffer(graphicsApi, 1, false)
    , m_textureIdBuffer(graphicsApi, 2, true)
    , m_modelsBuffer(graphicsApi, 3, true)
{
}

void Instance::SetTexturesIds(std::span<instancing::Vec1> data)
{
    m_textureIdBuffer.UploadData(data);
}

void Instance::SetModels(std::span<instancing::Matrix> data)
{
    m_modelsBuffer.UploadData(data);
}

void Instance::SetPositions(std::span<instancing::Vec3> data)
{
    m_positionsBuffer.UploadData(data);
}

void Instance::SetTextureCoordinates(std::span<instancing::Vec2> data)
{
    m_textureCoordinatesBuffer.UploadData(data);
}

void Instance::Bind() const
{
    m_positionsBuffer.Bind();
    m_textureCoordinatesBuffer.Bind();
    m_textureIdBuffer.Bind();
    m_modelsBuffer.Bind();
}

uint32_t Instance::GetIndicesCount() const
{
    return m_indexBuffer.GetCount();
}

uint32_t Instance::GetInstanceCount() const
{
    return m_modelsBuffer.GetCount();
}

uint32_t Instance::GetIndexBufferId() const
{
    return m_indexBuffer.GetId();
}
void Instance::SetIndices(std::span<uint32_t> data)
{
    m_indexBuffer.UploadData(data);
}
} // namespace renderer

