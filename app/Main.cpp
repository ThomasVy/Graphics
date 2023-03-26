#include <array>
#include <vector>
#include <string>
#include "str_utils/StringFormat.h"
#include "logger/Log.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "filesystem/IFilesystem.h"
#include "math/MatrixAndVectorMath.h"
#include "renderer/ShaderPipeline.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "Config.h"

static void ResizeWindowCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		logger::Debug("Yo");
	}
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        logger::Error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    auto err = glewInit();
    if (GLEW_OK != err)
    {
        logger::Error("Failed to initialize GLEW");
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, ResizeWindowCallback);  

    logger::Info("OPENGL Version {}\n", (char*)glGetString(GL_VERSION));

    std::array positions{
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    std::array indices{
        0u,1u,2u,
        2u,3u,0u
    };
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glfwSetKeyCallback(window, keyCallback);
    {
        my_math::mat4 proj = my_math::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        //my_math::mat4 view = my_math::translate(my_math::mat4(1.0f), my_math::vec3(-100, 0, 0));
        //my_math::mat4 model = my_math::translate(my_math::mat4{1.0f}, my_math::vec3(200, 200, 0));
        auto mvp = proj; // * view * model; //backwards because of column ordering in glm
        
        VertexArray va{};
        VertexBuffer vb{positions.data(), sizeof(float), positions.size()};
        IndexBuffer ib{indices.data(), indices.size()};
        VertexBufferLayout layout{};
        layout.Push<float>(2); //positions
        layout.Push<float>(2); //texture positions
        va.AddBuffer(vb, layout, ib );

        auto filesystem = GetFilesystem();
        ShaderPipeline shaderPipeline{filesystem.get()};
        Texture texture{BIN_LOCATION "/textures/ship.png"};
        texture.Bind();
        shaderPipeline.SetUniform("u_texture", 0);
        shaderPipeline.SetUniform("u_MVP", mvp);
        Renderer renderer{};
        while(!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            renderer.Draw(va, ib, shaderPipeline);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}