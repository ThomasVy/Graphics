#include "OpenGlApi.h"
#include "GLDebug.h"
#include "logger/Log.h"
#include <stdexcept>
#include "common/ConstExprMap.h"
#include <vector>
#include "Config.h"
namespace {

    constexpr std::string_view VERTEX_SHADER_PATH = BIN_LOCATION "/shaders/shader.vert";
    constexpr std::string_view FRAGMENT_SHADER_PATH = BIN_LOCATION "/shaders/shader.frag";

    constexpr std::array BUFFER_TYPE_TO_OPENGL{
        std::make_pair(graphics_api::IGraphicsApi::BufferType::Index, GL_ELEMENT_ARRAY_BUFFER),
        std::make_pair(graphics_api::IGraphicsApi::BufferType::Vertex, GL_ARRAY_BUFFER)
    };

    constexpr common::ConstExprMap BUFFER_TYPE_LOOKUP{BUFFER_TYPE_TO_OPENGL};

    constexpr std::array DATA_TYPE_TO_OPENGL{
        std::make_pair(graphics_api::DataType::Float, GL_FLOAT),
        std::make_pair(graphics_api::DataType::UInt32, GL_UNSIGNED_INT)
    };
    constexpr common::ConstExprMap DATA_TYPE_LOOKUP{DATA_TYPE_TO_OPENGL};

    constexpr std::array SHADERTYPE_TO_OPENGLENUM{
        std::make_pair(graphics_api::IGraphicsApi::ShaderType::Fragment, GL_FRAGMENT_SHADER),
        std::make_pair(graphics_api::IGraphicsApi::ShaderType::Vertex, GL_VERTEX_SHADER)
    };
    constexpr common::ConstExprMap SHADERTYPE_ENUM_LOOKUP{SHADERTYPE_TO_OPENGLENUM};
}

namespace graphics_api
{
    OpenGlApi::OpenGlApi(IFilesystem* filesystem, const int width, const int height)
        : m_vertexArray{0}
        , m_filesystem(filesystem)
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
        GLCALL(glBufferData(type, size, data, GL_DYNAMIC_DRAW));
    }
    
    void OpenGlApi::DeleteBuffer(uint32_t bufferId) const 
    {
        GLCALL(glDeleteBuffers(1, &bufferId));
    }
    
    void OpenGlApi::Clear() const 
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void OpenGlApi::SetBufferLayout(const uint32_t bufferId, const uint32_t index, const BufferInfo& element, uint32_t stride, bool isPerInstance ) const
    {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
        GLCALL(glEnableVertexAttribArray(index));
        auto type = DATA_TYPE_LOOKUP.at(element.type);
        auto normalized = element.normalized ? GL_TRUE : GL_FALSE;
		GLCALL(glVertexAttribPointer(index, element.count, type, normalized, stride, (const void *)element.offset));
        GLCALL(glVertexAttribDivisor(index, isPerInstance ? 1 : 0 ));
    }
    
    int OpenGlApi::GetUniformLocation(const uint32_t programId, std::string_view uniform) const
    {
        GLCALL(int location = glGetUniformLocation(programId, uniform.data()));
        return location;
    }
    
    void OpenGlApi::SetUniform(int location, const void * value, uint32_t count, UniformType type) const
    {
        switch (type)
        {
            case UniformType::Matrix4:
                GLCALL(glUniformMatrix4fv(location, count, GL_FALSE, static_cast<const GLfloat*>(value)));
                break;
            case UniformType::Vec4:
                GLCALL(glUniform4fv(location, count, static_cast<const GLfloat*>(value)));
                break;
            case UniformType::Int32:
                GLCALL(glUniform1iv(location, count, static_cast<const GLint*>(value)));
                break;
            case UniformType::UInt32:
                GLCALL(glUniform1uiv(location, count, static_cast<const GLuint*>(value)));
                break;
        }
    }
    
    uint32_t OpenGlApi::GenerateShader(ShaderType shaderType) const
    {
        uint32_t shaderId = 0;
        auto glType = SHADERTYPE_ENUM_LOOKUP.at(shaderType);
        GLCALL(shaderId = glCreateShader(glType));
        return shaderId;
    }
    
    void OpenGlApi::DeleteShader(uint32_t shaderId) const
    {
        GLCALL(glDeleteShader(shaderId));
    }
    
    void OpenGlApi::CompileShader(uint32_t shaderId, std::string_view shaderSource) const
    {
        // compile shader
        const char* data = shaderSource.data();
        GLCALL(glShaderSource(shaderId, 1, &data, NULL));
        GLCALL(glCompileShader(shaderId));

        // check for errors
        GLint success;
        GLCALL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));

        if (!success) {
            GLint logLength;
            GLCALL(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength));
            std::vector<char> log(logLength);
            GLCALL(glGetShaderInfoLog(shaderId, logLength, NULL, log.data()));

            logger::Error("SHADER compiling Failed:\n{}", log.data());
        }
    }
    
    uint32_t OpenGlApi::CreateShaderProgram() const
    {
        uint32_t shaderProgramId = 0;
        GLCALL(shaderProgramId = glCreateProgram());
        return shaderProgramId;
    }
    
    void OpenGlApi::DeleteShaderProgram(uint32_t shaderProgramId) const
    {
        GLCALL(glDeleteProgram(shaderProgramId));
    }
    
    void OpenGlApi::LinkShaders(uint32_t shaderProgramId, const std::vector<uint32_t>& shaderIds) const
    {
        for (const auto shaderId : shaderIds)
        {
            GLCALL(glAttachShader(shaderProgramId, shaderId));
        }
        GLCALL(glLinkProgram(shaderProgramId));
		GLCALL(glValidateProgram(shaderProgramId));
		GLint success;
		GLCALL(glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success));
		if (!success) {
			GLint logLength;
			GLCALL(glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &logLength));
			std::vector<char> log(logLength);
			GLCALL(glGetProgramInfoLog(shaderProgramId, logLength, NULL, log.data()));

			logger::Error("SHADER_PROGRAM linking");
            return;
		}
        GLCALL(glUseProgram(shaderProgramId));
    }
    
    std::optional<std::string> OpenGlApi::ReadShaderSourceFile(ShaderType shaderType)
    {
        std::string_view filePath;
        switch (shaderType)
        {
            case ShaderType::Fragment:
                filePath = FRAGMENT_SHADER_PATH;
                break;
            case ShaderType::Vertex:
                filePath = VERTEX_SHADER_PATH;
                break;
            default:
                logger::Error("Unknown Shader Type passed in");
                return std::nullopt;
        }
        std::optional<std::string> shaderSource = m_filesystem->ReadFile(filePath);        
        return shaderSource;
    }
    
    void OpenGlApi::DrawInstanced(uint32_t programId, uint32_t numberOfIndices, uint32_t numberOfInstances, bool wireFrameMode)
    { 
        GLCALL(glDrawElementsInstanced(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr, numberOfInstances));
        if (wireFrameMode)
        {
            uint32_t useSolidColor = 1;
            auto location = GetUniformLocation(programId, "u_useSolidColor");
            GLCALL(glUniform1ui(location, useSolidColor));
            GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

            GLCALL(glDrawElementsInstanced(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr, numberOfInstances));

            useSolidColor = 0;
            GLCALL(glUniform1ui(location, useSolidColor));
            GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
        }
    }
    
    void OpenGlApi::BindIndexBuffer(uint32_t indexBufferId) const
    {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
    }
}