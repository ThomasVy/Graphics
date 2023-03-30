#pragma once
#include <cstdint>
#include <span>
#include "graphics_api/IGraphicsApi.h"

class IndexBuffer {
public:
	IndexBuffer(graphics_api::IGraphicsApi* graphicsApi);
	~IndexBuffer();

	void UploadData(span<uint32_t> data);
	uint32_t GetCount() const;
	uint32_t GetId() const { return m_bufferID; }
private:
	graphics_api::IGraphicsApi* m_graphicsApi;
	uint32_t m_bufferID;
	size_t m_count;
};