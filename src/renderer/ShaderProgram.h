#pragma once

#include <string>
#include "math/MatrixAndVectorMath.h"
#include <unordered_map>
#include <vector>

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
    void SetUniform(std::string_view uniformName, const my_math::vec4& value);
    void SetUniform(std::string_view uniformName, const int value);
private:
    int GetUniformLocation(const std::string& uniformName);

    std::vector<Shader*> m_shaders;
    std::unordered_map<std::string, int> m_locationCache;
	uint32_t m_programId;
};