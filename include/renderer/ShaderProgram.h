#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "math/MatrixAndVectorMath.h"
#include "graphics_api/IGraphicsApi.h"

class Shader;

class ShaderProgram {
public:
    ShaderProgram(graphics_api::IGraphicsApi* graphicsApi);
    ~ShaderProgram();

	void LinkAndValidate() const;
    void AttachShader(Shader* shader);
    void Recompile();
    template <typename T>
    void SetUniform(std::string_view uniformName, const T* value, uint32_t count)
    {
        std::runtime_error("Generic version should not be called");
    }
    template<>
    void SetUniform<uint32_t>(std::string_view uniformName, const uint32_t* value, uint32_t count)
    {
        int location = GetUniformLocation(uniformName.data());
        m_graphicsApi->SetUniform(location, value, count, graphics_api::IGraphicsApi::UniformType::UInt32);
    }
    template<>
    void SetUniform<int>(std::string_view uniformName, const int* value, uint32_t count)
    {
        int location = GetUniformLocation(uniformName.data());
        m_graphicsApi->SetUniform(location, value, count, graphics_api::IGraphicsApi::UniformType::Int32);
    }


    template <>
    void SetUniform<my_math::vec4>(std::string_view uniformName, const my_math::vec4* value, uint32_t count)
    {
        int location = GetUniformLocation(uniformName.data());
        m_graphicsApi->SetUniform(location, my_math::value_ptr(*value), count, graphics_api::IGraphicsApi::UniformType::Vec4);
    }

    template <>
    void SetUniform<my_math::mat4>(std::string_view uniformName, const my_math::mat4* value, uint32_t count)
    {
        int location = GetUniformLocation(uniformName.data());
        m_graphicsApi->SetUniform(location, my_math::value_ptr(*value), count, graphics_api::IGraphicsApi::UniformType::Matrix4);
    }

    uint32_t GetShaderProgramId() const
    {
        return m_programId;
    }
private:
    int GetUniformLocation(const std::string& uniformName);

    graphics_api::IGraphicsApi* m_graphicsApi;
    std::vector<Shader*> m_shaders;
    std::unordered_map<std::string, int> m_locationCache;
	uint32_t m_programId;
};