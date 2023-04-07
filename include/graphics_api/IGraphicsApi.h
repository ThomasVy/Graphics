
#pragma once
#include <memory>
#include "BufferInfo.h"
#include <string>

namespace graphics_api
{
    class IGraphicsApi
    {
    public:
        enum class BufferType
        {
            Vertex,
            Index
        };
            
        virtual ~IGraphicsApi() = default;
        virtual uint32_t GenerateBuffers() const = 0;
        virtual void UploadBufferData(uint32_t bufferId, const void * data, uint64_t size, BufferType bufferType) const = 0;
        virtual void Draw(uint32_t vertexBufferId, uint32_t indexBufferId, uint32_t indexCount) const = 0;
        virtual void DeleteBuffer(uint32_t bufferId) const = 0;
        virtual void Clear() const = 0;
        virtual void SetBufferLayout(const uint32_t bufferId, const uint32_t index, const BufferInfo& element, uint32_t stride) const = 0;
        virtual int GetUniformLocation(const uint32_t programId, std::string_view uniform) const = 0;

        enum class UniformType
        {
            Matrix4,
            Vec4,
            Int32
        };
        virtual void SetUniform(int location, const void * value, uint32_t count, UniformType type) const = 0;
    protected:
        IGraphicsApi& operator=(const IGraphicsApi&) = default; 
    };
    enum class GraphicsType
    {
        OpenGL
    };
    std::unique_ptr<IGraphicsApi> GetGraphicsApi(GraphicsType graphics, const int width, const int height);
}