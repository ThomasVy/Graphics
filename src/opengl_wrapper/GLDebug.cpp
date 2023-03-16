#include "GLDebug.h"
#include "GL/glew.h"
#include "logger/Log.h"

void GLClearError()
{   
    while(glGetError() != GL_NO_ERROR );
}

bool GLLogCall(std::string_view function, std::string_view file, int line)
{
    if(auto error = glGetError(); error != GL_NO_ERROR){
        logger::Error("OpenGL error: {} {}:{}({})", function, file, line, error);
        return false;
    }
    return true;
}
