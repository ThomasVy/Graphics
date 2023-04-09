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

int main()
{
    int height = 600;
    int width = 800;
    auto filesystem = GetFilesystem();
    auto window = window_context::GetWindow(width, height, "LearnOpenGL");
    auto graphics = graphics_api::GetGraphicsApi(filesystem.get(), graphics_api::GraphicsType::OpenGL, width, height); 
    auto shaderPipeline = renderer::ShaderPipeline(graphics.get());
    Texture shipTexture(BIN_LOCATION "/textures/ship.png", 0);
    Texture diamondTexture(BIN_LOCATION "/textures/diamond.png", 1);
    renderer::SetTextures(shaderPipeline, {shipTexture, diamondTexture});
    auto ship = renderer::CreateQuad(0.0f, 0.0f, shipTexture);
    auto diamond = renderer::CreateQuad(-0.5f, 0.0f, diamondTexture);
    my_math::mat4 proj = my_math::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    my_math::mat4 view{1.0f};
    my_math::mat4 model{1.0f};
    auto mvp = proj * view * model; //backwards because of column ordering in glm
    VertexBuffer<renderer::Vertex2DInfo> shipVb(graphics.get());
    shipVb.UploadData(ship.vertexInfo);
    VertexBuffer<renderer::Vertex2DInfo> diamondVb(graphics.get());
    diamondVb.UploadData(diamond.vertexInfo);

    IndexBuffer ib(graphics.get());
    ib.UploadData(ship.indices);
    
    shaderPipeline.SetUniform("u_MVP", &mvp);
    Renderer renderer(graphics.get());
    while(!window->ShouldClose())
    {
        renderer.Clear();
        renderer.Draw(shipVb, ib);
        renderer.Draw(diamondVb, ib);
        window->SwapBuffers();
        window->PollEvents();
    }
}