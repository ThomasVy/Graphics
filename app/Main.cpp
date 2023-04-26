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
#include "window_context/IWindow.h"
#include "renderer/Vertex2DInfo.h"
#include "window_context/TimeStep.h"
#include "game/GameObject.h"
#include "renderer/Instance.h"

int main()
{
    int height = 600;
    int width = 800;
    auto filesystem = GetFilesystem();
    auto window = window_context::GetWindow(width, height, "LearnOpenGL");
    window->SwitchVSync(true);
    auto graphics = graphics_api::GetGraphicsApi(filesystem.get(), graphics_api::GraphicsType::OpenGL, width, height); 
    auto shaderPipeline = renderer::ShaderPipeline(graphics.get());
    auto shipTexture = Texture(BIN_LOCATION "/textures/ship.png", 0);
    auto diamondTexture = Texture(BIN_LOCATION "/textures/diamond.png", 1);
    renderer::SetTextures(shaderPipeline, {&shipTexture, &diamondTexture});
    
    auto textureIds = std::array<renderer::instancing::Vec1, 2>{(float)shipTexture.GetImageSlot(), (float)diamondTexture.GetImageSlot()};
    auto shipObject = game::GameObject(0.5f, my_math::vec3{0.0f, 0.0f, 1.0f}, 0.0f);
    auto diamondObject = game::GameObject(0.5f, my_math::vec3{0.0f, 1.0f, 1.0f}, 0.0f);
    auto models = std::array<renderer::instancing::Matrix, 2>{shipObject.GetModel(), diamondObject.GetModel()};
    auto object2D = renderer::instancing::CreateQuad(0.0f, 0.0f);
    renderer::Instance instance(graphics.get());
    instance.SetTexturesIds(textureIds);
    instance.SetModels(models);
    instance.SetPositions(object2D.positions);
    instance.SetTextureCoordinates(object2D.textureCoords);
    instance.SetIndices(object2D.indices);
    
    auto proj = my_math::ortho(-1.0f, 1.0f, -0.75f, 0.75f, -1.0f, 1.0f);
    my_math::mat4 view{1.0f};
    auto pv = proj * view; //backwards because of column ordering in glm
    shaderPipeline.SetUniform("u_PV", &pv);

    Renderer renderer(graphics.get());
    float lastFrameTime = 0;
    while(!window->ShouldClose())
    {
        auto time = window_context::GetCurrentTimeInSeconds();
        auto timestep = window_context::Timestep(time - lastFrameTime);
        lastFrameTime = time;

        //object.Update(timestep)
        renderer.Clear();
        //renderer.Draw(shipVb, ib);
        renderer.DrawInstance(instance);
        //renderer.Draw(diamondVb, ib);
        window->SwapBuffers();
        window->PollEvents();
    }
}