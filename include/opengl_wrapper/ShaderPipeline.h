#pragma once
#include <memory>

class ShaderPipeline
{
public:
    ShaderPipeline();
    void Recompile();
private:
    class Impl;
    std::unique_ptr<Impl, void (*)(Impl *)> m_impl;
};