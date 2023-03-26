
#pragma once
#include <memory>

namespace graphics
{
    class IGraphicsApi
    {
    public:
        virtual ~IGraphicsApi() = default;
    protected:
        IGraphicsApi& operator=(const IGraphicsApi&) = default; 
    };
    enum class GraphicsType
    {
        OpenGL
    };
    std::unique_ptr<IGraphicsApi> GetGraphicsApi(GraphicsType graphics, const int width, const int height);
}