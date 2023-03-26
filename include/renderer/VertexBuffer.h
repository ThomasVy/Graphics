#pragma once
#include <cstdint>
#include "graphics_api/IGraphicsApi.h"

class VertexBuffer {
public:
	VertexBuffer(const void* data, uint32_t typeSize, size_t count, graphics_api::IGraphicsApi* graphicsApi);
    ~VertexBuffer();

	uint32_t GetId() const { return m_bufferID;}

private:
	graphics_api::IGraphicsApi* m_graphicsApi;
	uint32_t m_bufferID;
};