#pragma once
#include <cstdint>

class VertexBuffer {
public:
	VertexBuffer(const void* data, uint32_t typeSize, size_t count);
    ~VertexBuffer();

	void Bind() const;
    void Unbind() const;
private:
	uint32_t m_bufferID;
};