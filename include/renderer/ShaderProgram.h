#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "graphics_api/opengl_wrapper/GLDebug.h"
#include "math/MatrixAndVectorMath.h"

class Shader;

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    void Bind() const;
    void Unbind() const;
	void LinkAndValidate() const;
    void AttachShader(Shader* shader);
    void DetachShader(Shader* shader);
    void Recompile();
    template <typename T>
    void SetUniform(std::string_view uniformName, const T& value)
    {
        std::runtime_error("Generic version should not be called");
    }
    template<>
    void SetUniform<int>(std::string_view uniformName, const int& value)
    {
        GLCALL(glUniform1i(GetUniformLocation(uniformName.data()), value));
    }

    template <>
    void SetUniform<my_math::vec4>(std::string_view uniformName, const my_math::vec4& value)
    {
        GLCALL(glUniform4fv(GetUniformLocation(uniformName.data()), 1, my_math::value_ptr(value)));
    }

    template <>
    void SetUniform<my_math::mat4>(std::string_view uniformName, const my_math::mat4& value)
    {
        GLCALL(glUniformMatrix4fv(GetUniformLocation(uniformName.data()), 1, GL_FALSE, my_math::value_ptr(value)));
    }

private:
    int GetUniformLocation(const std::string& uniformName);

    std::vector<Shader*> m_shaders;
    std::unordered_map<std::string, int> m_locationCache;
	uint32_t m_programId;
};