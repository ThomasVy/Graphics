#include "Renderer.h"
#include "graphics_api/opengl_wrapper/GLDebug.h"

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderPipeline& shaderPipeline) const
{
    vertexArray.Bind();
    indexBuffer.Bind();
    shaderPipeline.Bind();

    GLCALL(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
