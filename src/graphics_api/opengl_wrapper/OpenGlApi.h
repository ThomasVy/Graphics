#pragma once
#include "graphics_api/IGraphicsApi.h"

namespace graphics_api
{
    class OpenGlApi : public IGraphicsApi
    {
    public:
        OpenGlApi(const int width, const int height);
        ~OpenGlApi();
        uint32_t GenerateBuffers() const override;
        void UploadBufferData(uint32_t bufferId, const void * data, uint64_t size, BufferType bufferType) const override;
        void Draw(uint32_t vertexBufferId, uint32_t indexBufferId, uint32_t indexCount) const override;
        void DeleteBuffer(uint32_t bufferId) const override;
        void Clear() const override;
        void SetBufferLayout(const uint32_t bufferId, const uint32_t index, const BufferInfo& element, uint32_t stride) const override;

    private: 
        uint32_t m_vertexArray;
    };
}