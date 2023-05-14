#include "Texture.h"
#include <string>
#include "graphics_api/opengl_wrapper/GLDebug.h"
#include "logger/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

Texture::Texture(std::string path, uint32_t slot)
    : m_textureId(0)
    , m_filePath(std::move(path))
    , m_width(0)
    , m_height(0)
    , m_bitsPerPixel(0)
    , m_imageSlot(slot)
{
    //flips our image because opengl has 0,0 at the bottom right
    stbi_set_flip_vertically_on_load(1);
    auto* imageBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);
    if (!imageBuffer)
    {
        logger::Error("Error: Failed to load texture");
        logger::Error(stbi_failure_reason());
    }
    
    GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId));
    GLCALL(glTextureStorage2D(m_textureId, 1, GL_RGBA8, m_width, m_height));
    GLCALL(glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer));
    GLCALL(glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glBindTextureUnit(m_imageSlot, m_textureId));
    stbi_image_free(imageBuffer);
    imageBuffer = nullptr;
}

Texture::Texture(std::string path1, std::string path2)
{
   
    int width1=0, height1=0, nrComponents1 = 0;
    int width2=0, height2=0, nrComponents2 = 0;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data1 = stbi_load(path1.c_str() , &width1, &height1, &nrComponents1, 4);   // Load the first Image of size 512   X   512  (RGB)
    unsigned char* data2 = stbi_load(path2.c_str(), &width2, &height2, &nrComponents2, 4);  // Load the second  Image of size 512   X   512   (RGB)

    logger::Debug("ship {} {}", width1, height1);
    logger::Debug("diamond {} {}", width2, height2);
    glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_textureId);
    glTextureStorage3D(m_textureId, 1, GL_RGBA8, 45, 32, 2);
    glTextureSubImage3D(m_textureId, 0, 0, 0, 0, width1, height1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data1);
    glTextureSubImage3D(m_textureId, 0, 0, 0, 1, width2, height2, 1, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    GLCALL(glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glBindTextureUnit(0, m_textureId);
                
    stbi_image_free(data1);
    stbi_image_free(data2);
}

Texture::~Texture()
{
    GLCALL(glDeleteTextures(1, &m_textureId));
}