#pragma once
#include "Shape.h"
#include "graphics_api/IGraphicsApi.h"

namespace renderer
{
    Shape CreateQuad(graphics_api::IGraphicsApi* graphicsApi, float centerX, float centerY);
} // namespace renderer
