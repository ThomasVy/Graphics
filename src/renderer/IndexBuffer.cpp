#include "IndexBuffer.h"
#include "math/MatrixAndVectorMath.h"
IndexBuffer::IndexBuffer(::graphics_api::IGraphicsApi* graphicsApi)
    : m_graphicsApi(graphicsApi)
    , m_bufferID{m_graphicsApi->GenerateBuffers()}
    , m_count{0}
{
}

IndexBuffer::~IndexBuffer()
{
    m_graphicsApi->DeleteBuffer(m_bufferID);
}

uint32_t IndexBuffer::GetCount() const
{
    return static_cast<uint32_t>(m_count);
}

void IndexBuffer::UploadData(span<uint32_t> data)
{
    m_count = data.size();
	m_graphicsApi->UploadBufferData(m_bufferID, data, data.size_bytes(), ::graphics_api::IGraphicsApi::BufferType::Index);
}
