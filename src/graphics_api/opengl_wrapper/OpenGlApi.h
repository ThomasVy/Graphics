#pragma once
#include "graphics_api/IGraphicsApi.h"

namespace graphics
{
    class OpenGlApi : public IGraphicsApi
    {
    public:
        OpenGlApi(const int width, const int height);
    };
}