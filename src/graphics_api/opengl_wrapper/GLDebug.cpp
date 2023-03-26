#include "GLDebug.h"
#include "GL/glew.h"
#include "logger/Log.h"
#include "common/ConstExprMap.h"

using namespace std::literals::string_view_literals;
static constexpr std::array ERRORS_LOOKUP ={
    std::make_pair(0x0500u, "GL_INVALID_ENUM"sv),
    std::make_pair(0x0501u, "GL_INVALID_VALUE"sv),
    std::make_pair(0x0502u, "GL_INVALID_OPERATION"sv),
    std::make_pair(0x0506u, "GL_INVALID_FRAMEBUFFER_OPERATION"sv),
    std::make_pair(0xFFFFFFFFu, "GL_INVALID_INDEX"sv)
};

void GLClearError()
{   
    while(glGetError() != GL_NO_ERROR );
}

bool GLLogCall(std::string_view function, std::string_view file, int line)
{
    static constexpr auto LOOKUP_MAP = ConstExprMap{ERRORS_LOOKUP};
    if(auto error = glGetError(); error != GL_NO_ERROR){
        std::string_view errStr = "Uknown";
        try
        {
            errStr = LOOKUP_MAP.at(error);
        }
        catch(const std::exception&)
        {
        }
        
        logger::Error("OpenGL error: {} {}:{}({} - {})", function, file, line, error, errStr);
        return false;
    }
    return true;
}
