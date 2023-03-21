#include <array>
#include <vector>
#include <string>
#include "str_utils/StringFormat.h"
#include "logger/Log.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "opengl_wrapper/ShaderPipeline.h"
#include "filesystem/IFilesystem.h"
#include "math/MatrixAndVectorMath.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
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
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    std::array indices{
        0u,1u,2u,
        2u,3u,0u
    };

    glfwSetKeyCallback(window, keyCallback);
    {
        VertexArray va{};
        VertexBuffer vb{positions.data(), sizeof(float), positions.size()};
        IndexBuffer ib{indices.data(), indices.size()};
        VertexBufferLayout layout{};
        layout.Push<float>(2);
        va.AddBuffer(vb, layout, ib );

        auto filesystem = GetFilesystem();
        ShaderPipeline shaderPipeline{filesystem.get()};
        float red = 0.0f;
        float increment = 0.05f;
        while(!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            shaderPipeline.SetUniform("u_color", my_math::vec4{red, 0.1,0.1, 0});
            va.Bind();
            glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, nullptr);

            if (red > 1.0f)
                increment = -0.05f;
            else if (red < 0.0f)
                increment = 0.05f;

            red += increment;
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}