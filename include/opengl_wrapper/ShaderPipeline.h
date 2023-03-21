#pragma once
#include <memory>
#include "filesystem/IFilesystem.h"
#include "math/MatrixAndVectorMath.h"

class ShaderPipeline
{
public:
    ShaderPipeline( IFilesystem* filesystem );
    void Recompile();
    void SetUniform(std::string_view uniformName, const my_math::vec4& value );
private:
    class Impl;
    std::unique_ptr<Impl, void (*)(Impl *)> m_impl;
};