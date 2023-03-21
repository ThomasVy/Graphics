
#pragma once
#include <memory>

namespace graphics
{
    class IGraphicsApi
    {
    public:
        virtual ~IGraphicsApi() = 0;
    protected:
        IGraphicsApi& operator=(const IGraphicsApi&) = default; 
    };
    inline IGraphicsApi::~IGraphicsApi() {}

    enum class GraphicsType
    {
        OpenGL
    };
    std::unique_ptr<IGraphicsApi> GetGraphicsApi(GraphicsType graphics);
}