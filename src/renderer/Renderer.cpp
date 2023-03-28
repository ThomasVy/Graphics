#include "Renderer.h"

Renderer::Renderer(graphics_api::IGraphicsApi* graphicsApi)
    : m_graphicsApi{graphicsApi}
{
}

void Renderer::Clear() const
{
    m_graphicsApi->Clear();
}
