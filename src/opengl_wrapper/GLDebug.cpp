#include "GLDebug.h"
#include "GL/glew.h"
#include "logger/Log.h"
#include <unordered_map>
static std::unordered_map<uint32_t, std::string_view> ERRORS_LOOKUP ={
    {0x0500, "GL_INVALID_ENUM"},
    {0x0501, "GL_INVALID_VALUE"},
    {0x0502, "GL_INVALID_OPERATION"},
    {0x0506, "GL_INVALID_FRAMEBUFFER_OPERATION"},
    {0xFFFFFFFFu, "GL_INVALID_INDEX"}
};

void GLClearError()
{   
    while(glGetError() != GL_NO_ERROR );
}

bool GLLogCall(std::string_view function, std::string_view file, int line)
{
    if(auto error = glGetError(); error != GL_NO_ERROR){
        std::string_view errStr = "Uknown";
        try
        {
            errStr = ERRORS_LOOKUP.at(error);
        }
        catch(const std::exception&)
        {
        }
        
        logger::Error("OpenGL error: {} {}:{}({} - {})", function, file, line, error, errStr);
        return false;
    }
    return true;
}
