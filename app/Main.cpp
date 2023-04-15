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
#include "window_context/Time.h"
#include "game/GameObject.h"

int main()
{
    int height = 600;
    int width = 800;
    auto filesystem = GetFilesystem();
    auto window = window_context::GetWindow(width, height, "LearnOpenGL");
    auto graphics = graphics_api::GetGraphicsApi(filesystem.get(), graphics_api::GraphicsType::OpenGL, width, height); 
    auto shaderPipeline = renderer::ShaderPipeline(graphics.get());
    auto shipTexture = Texture(BIN_LOCATION "/textures/ship.png", 0);
    auto diamondTexture = Texture(BIN_LOCATION "/textures/diamond.png", 1);
    renderer::SetTextures(shaderPipeline, {&shipTexture, &diamondTexture});
    
    auto ship = renderer::CreateQuad(0.0f, 0.0f, shipTexture);
    
    auto diamond = renderer::CreateQuad(-0.5f, 0.0f, diamondTexture);
    auto proj = my_math::ortho(-1.0f, 1.0f, -0.75f, 0.75f, -1.0f, 1.0f);
    my_math::mat4 view{1.0f};
    auto pv = proj * view; //backwards because of column ordering in glm
    auto shipVb = VertexBuffer<renderer::Vertex2DInfo>(graphics.get());
    shipVb.UploadData(ship.vertexInfo);
    auto diamondVb = VertexBuffer<renderer::Vertex2DInfo>(graphics.get());
    diamondVb.UploadData(diamond.vertexInfo);

    auto ib = IndexBuffer(graphics.get());
    ib.UploadData(ship.indices);
    
    shaderPipeline.SetUniform("u_PV", &pv);
    Renderer renderer(graphics.get());
    float lastFrameTime = 0;
    auto shipObject = game::GameObject(0.5f, my_math::vec3{0.0f, 0.0f, 1.0f}, 0.0f);
    while(!window->ShouldClose())
    {
        auto time = window_context::GetCurrentTimeInSeconds();
        auto timestep = window_context::Timestep(time - lastFrameTime);
        lastFrameTime = time;

        //object.Update(timestep)
        renderer.Clear();
        renderer.Draw(shipVb, ib);
        renderer.Draw(diamondVb, ib);
        window->SwapBuffers();
        window->PollEvents();
    }
}