#include "Texture.h"
#include <string>
#include "graphics_api/opengl_wrapper/GLDebug.h"
#include "logger/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

Texture::Texture(std::string path, uint32_t slot, std::optional<my_math::vec2> eachSpriteSize)
    : m_textureId(0)
    , m_filePath(std::move(path))
    , m_width(0)
    , m_height(0)
    , m_bitsPerPixel(0)
    , m_imageSlot(slot)
    , m_eachSpriteSize(0.0f, 0.0f)
{
    //flips our image because opengl has 0,0 at the bottom right
    stbi_set_flip_vertically_on_load(1);
    auto* imageBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);
    if (!imageBuffer)
    {
        logger::Error("Error: Failed to load texture");
        logger::Error(stbi_failure_reason());
    }
    m_eachSpriteSize = eachSpriteSize.value_or(my_math::vec2{m_width, m_height});
    
    GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId));
    GLCALL(glTextureStorage2D(m_textureId, 1, GL_RGBA8, m_width, m_height));
    GLCALL(glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer));
    GLCALL(glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCALL(glBindTextureUnit(m_imageSlot, m_textureId));
    stbi_image_free(imageBuffer);
    imageBuffer = nullptr;
}

Texture::~Texture()
{
    GLCALL(glDeleteTextures(1, &m_textureId));
}