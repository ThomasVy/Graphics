#pragma once
#include <cstdint>
#include "graphics_api/IGraphicsApi.h"
#include <span>
template <typename T>
concept VertexInfo = 
  requires(T t) {
      { t.GetLayout() };
  };

template <VertexInfo T>
class VertexBuffer {
public:
	VertexBuffer(graphics_api::IGraphicsApi* graphicsApi)
	    : m_graphicsApi{graphicsApi}
    	, m_bufferID{m_graphicsApi->GenerateBuffers()}
	{
	}
    ~VertexBuffer()
	{
		m_graphicsApi->DeleteBuffer(m_bufferID);
	}

	void UploadData(std::span<T> data)
	{
		m_graphicsApi->UploadBufferData(m_bufferID, data.data(), data.size_bytes(), graphics_api::IGraphicsApi::BufferType::Vertex);
	}
	
	void Bind() const
	{
		const auto layout = T::GetLayout();
		for (auto i = 0u; i < layout.size(); ++i)
		{
			const auto &element = layout[i];
			m_graphicsApi->SetBufferLayout(m_bufferID, i, element, sizeof(T));
		}
	}
	
	uint32_t GetId() const { return m_bufferID;}

private:
	graphics_api::IGraphicsApi* m_graphicsApi;
	uint32_t m_bufferID;
};