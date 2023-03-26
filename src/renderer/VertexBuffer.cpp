#include "VertexBuffer.h"
#include "math/MatrixAndVectorMath.h"
VertexBuffer::VertexBuffer(const void* data, uint32_t typeSize, size_t count, graphics_api::IGraphicsApi* graphicsApi)
    : m_graphicsApi{graphicsApi}
    , m_bufferID{m_graphicsApi->GenerateBuffers()}
{
    m_graphicsApi->UploadBufferData(m_bufferID, data, count*typeSize, graphics_api::IGraphicsApi::BufferType::Vertex);
}

VertexBuffer::~VertexBuffer()
{
    m_graphicsApi->DeleteBuffer(m_bufferID);
}