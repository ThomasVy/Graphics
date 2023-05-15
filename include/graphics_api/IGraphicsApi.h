
#pragma once
#include <memory>
#include "BufferInfo.h"
#include <string>
#include <vector>
#include "filesystem/IFilesystem.h"

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
        virtual void Draw(uint32_t indexBufferId, uint32_t indexCount) const = 0;
        virtual void DeleteBuffer(uint32_t bufferId) const = 0;
        virtual void Clear() const = 0;
        virtual void SetBufferLayout(const uint32_t bufferId, const uint32_t index, const BufferInfo& element, uint32_t stride, bool isPerInstance) const = 0;
        virtual int GetUniformLocation(const uint32_t programId, std::string_view uniform) const = 0;

        enum class UniformType
        {
            Matrix4,
            Vec4,
            Int32,
            UInt32
        };
        virtual void SetUniform(int location, const void * value, uint32_t count, UniformType type) const = 0;

        enum class ShaderType
        {
            Vertex,
            Fragment
        };
        virtual uint32_t GenerateShader(ShaderType shaderType) const = 0;
        virtual void DeleteShader(uint32_t shaderId) const = 0;
        virtual void CompileShader(uint32_t shaderId, std::string_view shaderSource) const = 0;

        virtual uint32_t CreateShaderProgram() const = 0;
        virtual void DeleteShaderProgram(uint32_t shaderProgramId ) const = 0;
        virtual void LinkShaders(uint32_t shaderProgramId, const std::vector<uint32_t>& shaderIds) const = 0;
        virtual std::optional<std::string> ReadShaderSourceFile(ShaderType shaderType) = 0;
        virtual void DrawInstanced(uint32_t numberOfIndices, uint32_t numberOfInstances) = 0;
        virtual void BindIndexBuffer(uint32_t indexBufferId) const = 0;
    protected:
        IGraphicsApi& operator=(const IGraphicsApi&) = default; 
    };


    enum class GraphicsType
    {
        OpenGL
    };
    std::unique_ptr<IGraphicsApi> GetGraphicsApi( IFilesystem* filesystem, GraphicsType graphics, const int width, const int height);
}