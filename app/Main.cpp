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

static constexpr float SPEED = 1.0f;
static constexpr int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
using namespace std::string_view_literals;
static std::array CONTROLS { 
    "W"sv,
    "A"sv,
    "S"sv,
    "D"sv
};

int main()
{
    auto filesystem = GetFilesystem();
    auto ioFactory = io::GetIoFactory(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL");
    auto& window = ioFactory->GetWindow();
    window.SwitchVSync(true);
    auto& controls = ioFactory->GetControls(CONTROLS);
    auto& timer = ioFactory->GetTimer();
    auto& textDisplay = ioFactory->GetTextDisplay();
    auto graphics = graphics_api::GetGraphicsApi(filesystem.get(), graphics_api::GraphicsType::OpenGL, WINDOW_WIDTH, WINDOW_HEIGHT); 
    auto shaderPipeline = renderer::ShaderPipeline(graphics.get());

    auto shipTexture = Texture(BIN_LOCATION "/textures/ship.png", 0);
    auto diamondTexture = Texture(BIN_LOCATION "/textures/diamond.png", 1);
    renderer::SetTextures(shaderPipeline, {&shipTexture, &diamondTexture});
    auto quadShape = renderer::CreateQuad(graphics.get(), 0.0f, 0.0f);
    
    auto shipObject = game::GameObject(quadShape, shipTexture, 0.5f, my_math::vec3{0.0f, 0.0f, 0.0f}, 0.0f);
    std::vector<std::unique_ptr<renderer::IEntity>> diamondObjects{};

    for (int i = -50; i < 50; i++)
    {
        for (int j = -50 ; j < 50; j++)
        {
            diamondObjects.push_back(std::make_unique<game::GameObject>(quadShape, diamondTexture, 0.5f, my_math::vec3{i, j, 0.0f}, static_cast<float>(i+j)));
        } 
    }
    

    float aspect = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);
    renderer::Renderer renderer(graphics.get(), &shaderPipeline);

    auto camera = game::Camera(1.0f);
    camera.FollowObject(&shipObject);
    camera.SetProjection(my_math::perspective(glm::radians(45.0f), aspect, 0.01f, 1000.f));
    //my_math::ortho(-1.0f, 1.0f, -0.75f, 0.75f, -1.0f, 1.0f);

    while(!window.ShouldClose())
    {
        renderer.Clear(); //has to be at the top
        float timeElapsed = timer.GetMillisecondsElapsed();
        float scrollValue = static_cast<float>(0.5*-controls.GetScrollDelta());
        camera.AddZoom(scrollValue);

        game::ClearVelocity(shipObject);
        if (controls.IsKeyHeld("W"))
        {
            shipObject.SetYVelocity(SPEED);
        }
        if (controls.IsKeyHeld("S"))
        {
            shipObject.SetYVelocity(-SPEED);
        }
        if (controls.IsKeyHeld("A"))
        {
            shipObject.SetXVelocity(-SPEED);
        }
        if (controls.IsKeyHeld("D"))
        {
            shipObject.SetXVelocity(SPEED);
        }

        shipObject.Update(timeElapsed);
        camera.Update(timeElapsed);

        renderer.SetViewProj(camera.GetViewProjectionMatrix());
        renderer.DrawEntities(diamondObjects); 
        renderer.DrawEntity(shipObject); 

        textDisplay.Render();
        controls.Clear();
        ioFactory->Refresh();
    }
}