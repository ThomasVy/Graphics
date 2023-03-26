#include "OpenGlApi.h"
#include "GL/glew.h"
#include "logger/Log.h"
#include <stdexcept>

namespace graphics
{
    OpenGlApi::OpenGlApi(const int width, const int height)
    {
        auto err = glewInit();
        if (err != GLEW_OK)
        {
            logger::Error("Failed to initialize GLEW");
            std::runtime_error("Failed to initialize GLEW");
        }
        glViewport(0, 0, width, height);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        logger::Info("OPENGL Version {}\n", (char*)glGetString(GL_VERSION));
    }
}