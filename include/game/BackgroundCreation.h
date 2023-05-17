#pragma once
#include <memory>
#include <span>
#include "renderer/IEntity.h"
#include "renderer/Shape.h"
#include "renderer/SubTexture.h"

namespace game
{
    std::vector<std::unique_ptr<renderer::IEntity>> GenerateFloorTiles(
        const renderer::Shape &shape,
        std::span<const renderer::SubTexture> floorTiles);
} // namespace game
