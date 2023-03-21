#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderPipeline.h"

class Renderer 
{
public:
    void Clear() const;
    void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderPipeline& shaderPipeline) const;
};
