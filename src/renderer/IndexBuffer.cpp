#include "IndexBuffer.h"
#include "math/MatrixAndVectorMath.h"
IndexBuffer::IndexBuffer(const uint32_t* data, size_t count, ::graphics_api::IGraphicsApi* graphicsApi)
    : m_graphicsApi(graphicsApi)
    , m_bufferID{m_graphicsApi->GenerateBuffers()}
    , m_count(count)
{
    m_graphicsApi->UploadBufferData(m_bufferID, data, count*sizeof(uint32_t), ::graphics_api::IGraphicsApi::BufferType::Index);
}

IndexBuffer::~IndexBuffer()
{
    m_graphicsApi->DeleteBuffer(m_bufferID);
}

uint32_t IndexBuffer::GetCount() const
{
    return static_cast<uint32_t>(m_count);
}

