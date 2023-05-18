#include "BackgroundCreation.h"
#include "math/Random.h"
#include "GameObject.h"
#include "logger/Log.h"
#include "math/MatrixAndVectorMath.h"
static constexpr float TILE_SIZE = 0.5f;

namespace game
{
    std::vector<std::unique_ptr<renderer::IEntity>> GenerateFloorTiles(
        const renderer::Shape &shape,
        std::span<const renderer::SubTexture> floorTiles)
    {
        auto floorObjects = std::vector<std::unique_ptr<renderer::IEntity>>{};
        for (float i = -15; i < 15; i += 0.5f)
        {
            for (float j = -15; j < 15; j += 0.5f)
            {
                auto randomIndex = math::integer::Random(0, (int)floorTiles.size() - 1);
                floorObjects.push_back(std::make_unique<game::GameObject>(
                    shape,
                    &(floorTiles[randomIndex]),
                    TILE_SIZE,
                    my_math::vec3{i, j, 0.0f},
                    0.0f));
            }
        }
        return floorObjects;
    }
} // namespace game
