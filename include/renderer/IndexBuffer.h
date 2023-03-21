#pragma once
#include <cstdint>

class IndexBuffer {
public:
	IndexBuffer(const uint32_t* data, size_t count);
	~IndexBuffer();
	void Bind() const;
    void Unbind() const;

	uint32_t GetCount() const;
private:
	uint32_t m_bufferID;
	size_t m_count;
};