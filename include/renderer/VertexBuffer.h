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
	
	//bindings the layout starting at the starting index 
	//returns the ending index
	uint32_t Bind(uint32_t startingIndex) const
	{
		const auto layout = T::GetLayout();
		auto i = startingIndex;
		for (const auto& element : layout)
		{
			m_graphicsApi->SetBufferLayout(m_bufferID, i, element, sizeof(T));
			++i;
		}
		return i;
	}
	
	uint32_t GetId() const { return m_bufferID;}

private:
	graphics_api::IGraphicsApi* m_graphicsApi;
	uint32_t m_bufferID;
};