#include <array>
#include <vector>

#include <string>

#include "str_utils/StringFormat.h"
#include "logger/Log.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "opengl_wrapper/ShaderPipeline.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(std::string_view function, std::string_view file, int line)
{
    if(auto error = glGetError(); error != GL_NO_ERROR){
        logger::Error("OpenGL error: {} {}:{}({})", function, file, line, error);
        return false;
    }
    return true;
}

static void ResizeWindowCallback(GLFWwindow* window, int width, int height)
{
    GLCALL(glViewport(0, 0, width, height));
}  

template <typename T, std::size_t Size> 
static uint32_t GetArrayByteSize(const std::array<T, Size>& arr)
{
    return Size*sizeof(T);
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
    auto err = glewInit();
    if (GLEW_OK != err)
    {
        logger::Error("Failed to initialize GLEW");
        glfwTerminate();
        return -1;
    }
    GLCALL(glViewport(0, 0, 800, 600));
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
    unsigned int VAO{};
    GLCALL(glGenVertexArrays(1, &VAO));
    GLCALL(glBindVertexArray(VAO));

    uint32_t buffer{};
    GLCALL(glGenBuffers(1, &buffer));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, GetArrayByteSize(positions), positions.data(), GL_STATIC_DRAW));

    uint32_t ibo{};
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetArrayByteSize(indices), indices.data(), GL_STATIC_DRAW));

    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0));

    {
        ShaderPipeline shaderPipeline;
        while(!glfwWindowShouldClose(window))
        {
            GLCALL(glClear(GL_COLOR_BUFFER_BIT));
            GLCALL(glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, nullptr));
            glfwSwapBuffers(window);
            glfwPollEvents(); 
        }
    }
    glfwTerminate();
    return 0;
}