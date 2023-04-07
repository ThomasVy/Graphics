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
    std::array vertices{
        Vertex2DInfo{.positions={-0.5f, -0.5f}, .textureCoordinates={0.0f, 0.0f}},
        Vertex2DInfo{.positions={0.5f, -0.5f}, .textureCoordinates={1.0f, 0.0f}},
        Vertex2DInfo{.positions={0.5f, 0.5f}, .textureCoordinates={1.0f, 1.0f}},
        Vertex2DInfo{.positions={-0.5f, 0.5f}, .textureCoordinates={0.0f, 1.0f}}
    };
    std::array indices{
        0u,1u,2u,
        2u,3u,0u
    };
    my_math::mat4 proj = my_math::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    my_math::mat4 view{1.0f};
    my_math::mat4 model{1.0f};
    auto mvp = proj * view * model; //backwards because of column ordering in glm
    VertexBuffer<Vertex2DInfo> vb(graphics.get());
    vb.UploadData(vertices);
    IndexBuffer ib(graphics.get());
    ib.UploadData(indices);
    ShaderPipeline shaderPipeline(graphics.get());
    Texture texture(BIN_LOCATION "/textures/ship.png");
    texture.Bind();
    shaderPipeline.SetUniform("u_texture", 0);
    shaderPipeline.SetUniform("u_MVP", mvp);
    Renderer renderer(graphics.get());
    while(!window->ShouldClose())
    {
        renderer.Clear();
        renderer.Draw(vb, ib);
        window->SwapBuffers();
        window->PollEvents();
    }
}