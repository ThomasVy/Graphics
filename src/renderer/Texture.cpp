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
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_textureId));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer));
    stbi_image_free(imageBuffer);
    imageBuffer = nullptr;
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
    GLCALL(glDeleteTextures(1, &m_textureId));
}

void Texture::Bind() const
{
    GLCALL(glBindTextureUnit(m_imageSlot, m_textureId));
}