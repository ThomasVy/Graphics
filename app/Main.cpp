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
#include "renderer/Vertex2DInfo.h"
#include "game/GameObject.h"
#include "renderer/Instance.h"
#include "io/IoFactory.h"

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
    
    auto object2D = renderer::instancing::CreateQuad(0.0f, 0.0f);
    renderer::Instance instance(graphics.get(), &shaderPipeline);
    instance.SetPositions(object2D.positions);
    instance.SetTextureCoordinates(object2D.textureCoords);
    instance.SetIndices(object2D.indices);
    instance.SetTextureId(shipTexture.GetImageSlot());

    auto diamondInstance = renderer::Instance(graphics.get(), &shaderPipeline);
    diamondInstance.SetPositions(object2D.positions);
    diamondInstance.SetTextureCoordinates(object2D.textureCoords);
    diamondInstance.SetIndices(object2D.indices);
    diamondInstance.SetTextureId(diamondTexture.GetImageSlot());

    float aspect = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);
    Renderer renderer(graphics.get());
    auto shipObject = game::GameObject(0.5f, my_math::vec3{0.0f, 0.0f, 0.0f}, 0.0f);
    auto diamondObject = game::GameObject(0.5f, my_math::vec3{0.0f, 1.0f, 0.0f}, 0.0f);
    float distance = 1.0f;
    //const auto proj = my_math::ortho(-1.0f, 1.0f, -0.75f, 0.75f, -1.0f, 1.0f);
    const auto proj = my_math::perspective(glm::radians(45.0f), aspect, 0.01f, 1000.f);

    while(!window.ShouldClose())
    {
        renderer.Clear(); //has to be at the top
        float timeElapsed = timer.GetMillisecondsElapsed();
        float scrollValue = 0.5*(double)-controls.GetScrollDelta();
        distance += scrollValue;
        if (distance < 1.0f) distance = 1.0f;
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

        auto pos = shipObject.GetPosition();
        my_math::vec3 eye = my_math::vec3(pos.x, pos.y, distance); //position of the camera
        my_math::vec3 center = my_math::vec3(pos.x, pos.y, 0.0f); //where the camera is looking at
        my_math::vec3 up = my_math::vec3(0.0f, 1.0f, 0.0f);
        my_math::mat4 view = my_math::lookAt(eye, center, up);
        auto pv = proj * view; //backwards because of column ordering in glm
        shaderPipeline.SetUniform("u_PV", &pv);

        auto models = std::array<renderer::instancing::Matrix, 1>{shipObject.GetModel()};
        instance.SetModels(models);
        auto model2 =  std::array<renderer::instancing::Matrix, 1>{diamondObject.GetModel()};
        diamondInstance.SetModels(model2);
        renderer.DrawInstance(instance);
        renderer.DrawInstance(diamondInstance);
        textDisplay.Render();
        controls.Clear();
        ioFactory->Refresh();
    }
}