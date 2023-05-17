#pragma once
#include "Shape.h"
#include "graphics_api/IGraphicsApi.h"

namespace renderer
{
    Shape CreateQuad(graphics_api::IGraphicsApi* graphicsApi);
    Shape CreateQuadSpriteSheet(graphics_api::IGraphicsApi* graphicsApi);
} // namespace renderer
