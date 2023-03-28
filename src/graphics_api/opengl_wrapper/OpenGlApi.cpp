#include "OpenGlApi.h"
#include "GLDebug.h"
#include "logger/Log.h"
#include <stdexcept>
#include "common/ConstExprMap.h"

namespace {
    constexpr std::array BUFFER_TYPE_TO_OPENGL{
        std::make_pair(graphics_api::IGraphicsApi::BufferType::Index, GL_ELEMENT_ARRAY_BUFFER),
        std::make_pair(graphics_api::IGraphicsApi::BufferType::Vertex, GL_ARRAY_BUFFER)
    };

    constexpr ConstExprMap BUFFER_TYPE_LOOKUP{BUFFER_TYPE_TO_OPENGL};

    constexpr std::array DATA_TYPE_TO_OPENGL{
        std::make_pair(graphics_api::DataType::Float, GL_FLOAT)
    };
    constexpr ConstExprMap DATA_TYPE_LOOKUP{DATA_TYPE_TO_OPENGL};
}

namespace graphics_api
{
    OpenGlApi::OpenGlApi(const int width, const int height)
        : m_vertexArray{0}
    {
        auto err = glewInit();
        if (err != GLEW_OK)
        {
            logger::Error("Failed to initialize GLEW");
            std::runtime_error("Failed to initialize GLEW");
        }
        GLCALL(glViewport(0, 0, width, height));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glGenVertexArrays(1, &m_vertexArray));
        GLCALL(glBindVertexArray(m_vertexArray));
        logger::Info("OPENGL Version {}\n", (char*)glGetString(GL_VERSION));
    }
    
    OpenGlApi::~OpenGlApi()
    {
        GLCALL(GLCALL(glDeleteVertexArrays(1, &m_vertexArray)));
    }
    
    uint32_t OpenGlApi::GenerateBuffers() const 
    {
        uint32_t bufferId = 0;
        GLCALL(glGenBuffers(1, &bufferId));
        return bufferId;
    }
    
    void OpenGlApi::UploadBufferData(uint32_t bufferId, const void * data, uint64_t size, BufferType bufferType) const 
    {
        auto type = BUFFER_TYPE_LOOKUP.at(bufferType);
        GLCALL(glBindBuffer(type, bufferId));
        GLCALL(glBufferData(type, size, data, GL_STATIC_DRAW));
    }
    
    void OpenGlApi::Draw(uint32_t vertexBufferId, uint32_t indexBufferId, uint32_t indexCount) const 
    {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
        GLCALL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
    }
    
    void OpenGlApi::DeleteBuffer(uint32_t bufferId) const 
    {
        GLCALL(glDeleteBuffers(1, &bufferId));
    }
    
    void OpenGlApi::Clear() const 
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void OpenGlApi::SetBufferLayout(const uint32_t bufferId, const uint32_t index, const BufferInfo& element, uint32_t stride) const
    {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
        GLCALL(glEnableVertexAttribArray(index));
        auto type = DATA_TYPE_LOOKUP.at(element.type);
        auto normalized = element.normalized ? GL_TRUE : GL_FALSE;
		GLCALL(glVertexAttribPointer(index, element.count, type, normalized, stride, (const void *)element.offset));
    }
}