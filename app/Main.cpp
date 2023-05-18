#include <array>
#include <vector>
#include <string>
#include "str_utils/StringFormat.h"
#include "logger/Log.h"
#include "filesystem/IFilesystem.h"
#include "math/MatrixAndVectorMath.h"
#include "renderer/ShaderPipeline.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "Config.h"
#include "graphics_api/IGraphicsApi.h"
#include "game/GameObject.h"
#include "io/IoFactory.h"
#include "renderer/CreateShapes.h"
#include "game/Camera.h"
#include "game/BackgroundCreation.h"
#include "game/TextWindows.h"

static constexpr float DEFAULT_SPEED = 1.0f;
static constexpr int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
using namespace std::string_view_literals;

int main()
{
    auto filesystem = GetFilesystem();
    auto ioFactory = io::GetIoFactory(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL");
    auto& window = ioFactory->GetWindow();
    window.SwitchVSync(true);
    auto& controls = ioFactory->GetControls();
    auto& timer = ioFactory->GetTimer();
    auto& textDisplay = ioFactory->GetTextDisplay();
    textDisplay.AddTextWindow(1, game::RenderFPSCounter);
    textDisplay.AddTextWindow(2, game::RenderControlsHelp);

    auto graphics = graphics_api::GetGraphicsApi(filesystem.get(), graphics_api::GraphicsType::OpenGL, WINDOW_WIDTH, WINDOW_HEIGHT); 
    auto shaderPipeline = renderer::ShaderPipeline(graphics.get());

    auto quadShape = renderer::CreateQuadSpriteSheet(graphics.get());

    auto shipSheet = Texture(BIN_LOCATION "/textures/ship.png", 0);
    auto diamondSheet = Texture(BIN_LOCATION "/textures/diamond.png", 1);
    auto spriteTextureSheet = Texture(BIN_LOCATION "/textures/tilemap_packed.png", 2, my_math::vec2{16.0f, 16.0f});
    renderer::SetTextures(shaderPipeline, {&shipSheet, &diamondSheet, &spriteTextureSheet});

    auto shipTexture = renderer::SubTexture(shipSheet, {0.0f, 0.0f});
    auto diamondTexture = renderer::SubTexture(diamondSheet, {0.0f, 0.0f});

    auto knightTextures = std::array{
        renderer::SubTexture(spriteTextureSheet, {1.0f, 2.0f}),
        renderer::SubTexture(spriteTextureSheet, {0.0f, 2.0f})
    };
    int knightIndex = 0;
    const auto sandFloorTiles = std::array{
        renderer::SubTexture{spriteTextureSheet, {0.0f, 6.0f}},
        renderer::SubTexture{spriteTextureSheet, {1.0f, 6.0f}},
        renderer::SubTexture{spriteTextureSheet, {2.0f, 6.0f}},
        renderer::SubTexture{spriteTextureSheet, {3.0f, 6.0f}},
        renderer::SubTexture{spriteTextureSheet, {4.0f, 6.0f}},
        renderer::SubTexture{spriteTextureSheet, {5.0f, 6.0f}},
        renderer::SubTexture{spriteTextureSheet, {6.0f, 7.0f}},
        renderer::SubTexture{spriteTextureSheet, {6.0f, 8.0f}}};
    

    auto floorObjects = game::GenerateFloorTiles(quadShape, sandFloorTiles);
    auto player = game::GameObject(quadShape, &knightTextures[knightIndex], 0.5f, my_math::vec3{0.0f, 0.0f, 0.0f}, 0.0f);
    std::vector<std::unique_ptr<renderer::IEntity>> backgroundTiles{};


    float aspect = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);
    renderer::Renderer renderer(graphics.get(), &shaderPipeline);

    auto camera = game::Camera(1.0f);
    camera.FollowObject(&player);
    camera.SetProjection(my_math::perspective(glm::radians(45.0f), aspect, 0.01f, 1000.f));
    //my_math::ortho(-1.0f, 1.0f, -0.75f, 0.75f, -1.0f, 1.0f);
    bool wireFrameMode = false;
    float playerSpeed = DEFAULT_SPEED;
    while(!window.ShouldClose())
    {
        renderer.Clear(); //has to be at the top
        float timeElapsed = timer.GetMillisecondsElapsed();
        float scrollValue = static_cast<float>(0.5*-controls.GetScrollDelta());
        camera.AddZoom(scrollValue);

        game::ClearVelocity(player);
        if (controls.IsKeyHeld("LEFT_SHIFT"))
        {
            playerSpeed *= 2.0;
        }
        if (controls.IsKeyHeld("W"))
        {
            player.SetYVelocity(playerSpeed);
        }
        if (controls.IsKeyHeld("S"))
        {
            player.SetYVelocity(-playerSpeed);
        }
        if (controls.IsKeyHeld("A"))
        {
            player.SetXVelocity(-playerSpeed);
        }
        if (controls.IsKeyHeld("D"))
        {
            player.SetXVelocity(playerSpeed);
        }
        if (controls.WasKeyPressed("Q"))
        {
            wireFrameMode = !wireFrameMode;
        }
        if (controls.WasKeyPressed("E"))
        {
            knightIndex++;
            knightIndex %= 2;
            player.SetTexture(&knightTextures[knightIndex]);
        }

        player.Update(timeElapsed);
        camera.Update(timeElapsed);

        renderer.SetViewProj(camera.GetViewProjectionMatrix());
        renderer.DrawEntities(floorObjects, wireFrameMode); 
        renderer.DrawEntity(player, wireFrameMode); 

        playerSpeed = DEFAULT_SPEED;
        textDisplay.RenderTextWindows();
        controls.Clear();
        ioFactory->Refresh();
    }
}