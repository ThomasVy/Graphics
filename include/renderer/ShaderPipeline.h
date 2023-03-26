#pragma once
#include <memory>
#include "filesystem/IFilesystem.h"
#include "math/MatrixAndVectorMath.h"
#include "ShaderProgram.h"
#include "Shader.h"

class ShaderPipeline
{
public:
    ShaderPipeline( IFilesystem* filesystem );
    void Recompile();
    void Bind() const;
    void Unbind() const;
    template <typename T>
    void SetUniform(std::string_view uniformName, const T& value)
    {
        m_shaderProgram->SetUniform(uniformName, value);
    }
private:
    std::unique_ptr<ShaderProgram> m_shaderProgram;
    std::unique_ptr<Shader> m_vertexShader;
    std::unique_ptr<Shader> m_fragmentShader;
};