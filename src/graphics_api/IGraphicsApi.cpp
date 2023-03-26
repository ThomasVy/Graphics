#include "IGraphicsApi.h"
#include "opengl_wrapper/OpenGlApi.h"
#include "logger/Log.h"
std::unique_ptr<graphics_api::IGraphicsApi> graphics_api::GetGraphicsApi(graphics_api::GraphicsType graphics, const int width, const int height)
{
    switch(graphics)
    {
    case graphics_api::GraphicsType::OpenGL:
        return std::make_unique<graphics_api::OpenGlApi>(width, height);
    default: 
        logger::Error("Unknown graphics type");
        break;
    }
    return nullptr;
}