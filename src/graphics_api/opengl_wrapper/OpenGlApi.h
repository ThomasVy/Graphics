#pragma once
#include "graphics_api/IGraphicsApi.h"
#include "filesystem/IFilesystem.h"

namespace graphics_api
{
    class OpenGlApi : public IGraphicsApi
    {
    public:
        OpenGlApi(IFilesystem* filesystem, const int width, const int height);
        ~OpenGlApi();
        uint32_t GenerateBuffers() const override;
        void UploadBufferData(uint32_t bufferId, const void * data, uint64_t size, BufferType bufferType) const override;
        void Draw(uint32_t vertexBufferId, uint32_t indexBufferId, uint32_t indexCount) const override;
        void DeleteBuffer(uint32_t bufferId) const override;
        void Clear() const override;
        void SetBufferLayout(const uint32_t bufferId, const uint32_t index, const BufferInfo& element, uint32_t stride) const override;
        int GetUniformLocation(const uint32_t programId, std::string_view uniform) const override;
        void SetUniform(int location, const void * value, uint32_t count, UniformType type) const override;
        uint32_t GenerateShader(ShaderType shaderType) const override;
        void DeleteShader(uint32_t shaderId) const override;
        void CompileShader(uint32_t shaderId, std::string_view shaderSource) const override;

        uint32_t CreateShaderProgram() const override;
        void DeleteShaderProgram(uint32_t shaderProgramId ) const override;
        void LinkShaders(uint32_t shaderProgramId, const std::vector<uint32_t>& shaderIds) const override;
        std::optional<std::string> ReadShaderSourceFile(ShaderType shaderType) override;
    private: 
        uint32_t m_vertexArray;
        IFilesystem* m_filesystem;
    };
}