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
	VertexBuffer(graphics_api::IGraphicsApi* graphicsApi, uint32_t index, bool isPerInstance)
	    : m_graphicsApi{graphicsApi}
    	, m_bufferID{m_graphicsApi->GenerateBuffers()}
		, m_index(index)
		, m_count(0)
		, m_isPerInstance(isPerInstance)
	{
	}
	
    ~VertexBuffer()
	{
		m_graphicsApi->DeleteBuffer(m_bufferID);
	}

	void UploadData(std::span<T> data)
	{
		m_count = static_cast<uint32_t>(data.size());
		m_graphicsApi->UploadBufferData(m_bufferID, data.data(), data.size_bytes(), graphics_api::IGraphicsApi::BufferType::Vertex);
	}
	
	//bindings the layout starting at the starting index 
	//returns the ending index
	void Bind() const
	{
		const auto layout = T::GetLayout();
		auto i = m_index;
		for (const auto& element : layout)
		{
			m_graphicsApi->SetBufferLayout(m_bufferID, i, element, sizeof(T), m_isPerInstance);
			++i;
		}
	}
	
	uint32_t GetId() const { return m_bufferID;}
	uint32_t GetCount() const { return m_count; }
private:
	graphics_api::IGraphicsApi* m_graphicsApi;
	uint32_t m_bufferID;
	uint32_t m_index;
	uint32_t m_count;
	bool m_isPerInstance;
};