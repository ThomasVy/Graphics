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
#include "renderer/VertexArray.h"
#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "Config.h"
#include "graphics_api/IGraphicsApi.h"
#include "window_context/IWindow.h"

int main()
{
    int height = 600;
    int width = 800;
    auto filesystem = GetFilesystem();
    auto window = window_context::GetWindow(width, height, "LearnOpenGL");
    auto graphics = graphics::GetGraphicsApi(graphics::GraphicsType::OpenGL, width, height); 
    std::array vertices{
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    std::array indices{
        0u,1u,2u,
        2u,3u,0u
    };
    my_math::mat4 proj = my_math::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    my_math::mat4 view{1.0f};
    my_math::mat4 model{1.0f};
    auto mvp = proj * view * model; //backwards because of column ordering in glm
    
    VertexArray va{};
    VertexBuffer vb{vertices.data(), sizeof(float), vertices.size()};
    IndexBuffer ib{indices.data(), indices.size()};
    VertexBufferLayout layout{};
    layout.Push<float>(2); //positions
    layout.Push<float>(2); //texture positions
    va.AddBuffer(vb, layout, ib );
    ShaderPipeline shaderPipeline{filesystem.get()};
    Texture texture{BIN_LOCATION "/textures/ship.png"};
    texture.Bind();
    shaderPipeline.SetUniform("u_texture", 0);
    shaderPipeline.SetUniform("u_MVP", mvp);
    Renderer renderer{};
    while(!window->ShouldClose())
    {
        renderer.Clear();
        renderer.Draw(va, ib, shaderPipeline);
        window->SwapBuffers();
        window->PollEvents();
    }
}