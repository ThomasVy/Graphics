#pragma once
#include <cstdint>
#include "graphics_api/IGraphicsApi.h"

class IndexBuffer {
public:
	IndexBuffer(const uint32_t* data, size_t count, graphics_api::IGraphicsApi* graphicsApi);
	~IndexBuffer();

	uint32_t GetCount() const;
	uint32_t GetId() const { return m_bufferID; }
private:
	graphics_api::IGraphicsApi* m_graphicsApi;
	uint32_t m_bufferID;
	size_t m_count;
};
