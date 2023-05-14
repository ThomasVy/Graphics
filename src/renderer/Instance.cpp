#include "Instance.h"
namespace renderer
{
Instance::Instance(graphics_api::IGraphicsApi* graphicsApi, ShaderPipeline* pipeline)
    : m_pipeline(pipeline)
    , m_indexBuffer(graphicsApi)
    , m_positionsBuffer(graphicsApi, 0, false)
    , m_textureCoordinatesBuffer(graphicsApi, 1, false)
    , m_modelsBuffer(graphicsApi, 2, true)
    , m_textureId(0)
{
}

void Instance::SetTextureId(uint32_t textureId)
{
    m_textureId = textureId;
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
    m_modelsBuffer.Bind();
    m_pipeline->SetUniform("u_texId", &m_textureId);
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

