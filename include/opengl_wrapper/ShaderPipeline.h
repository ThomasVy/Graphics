#pragma once
#include <memory>
#include "filesystem/IFilesystem.h"

class ShaderPipeline
{
public:
    ShaderPipeline( IFilesystem* filesystem );
    void Recompile();
private:
    class Impl;
    std::unique_ptr<Impl, void (*)(Impl *)> m_impl;
};