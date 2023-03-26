#include "IGraphicsApi.h"
#include "OpenGlApi.h"
#include "logger/Log.h"
std::unique_ptr<graphics::IGraphicsApi> graphics::GetGraphicsApi(graphics::GraphicsType graphics, const int width, const int height)
{
    switch(graphics)
    {
    case graphics::GraphicsType::OpenGL:
        return std::make_unique<OpenGlApi>(width, height);
    default: 
        logger::Error("Unknown graphics type");
        break;
    }
    return nullptr;
}