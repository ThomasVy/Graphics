#pragma once
#include <string>
#include "math/MatrixAndVectorMath.h"
#include <optional>

class Texture
{
public:
    Texture(std::string path, uint32_t slot, std::optional<my_math::vec2> eachSpriteSize = std::nullopt);
    ~Texture();
    Texture(const Texture&) = delete;
    int GetWidth() const {return m_width;}
    int GetHeight() const { return m_height; }
    inline uint32_t GetImageSlot() const {return m_imageSlot;}
    const my_math::vec2& GetSpriteSize() const {return m_eachSpriteSize;}
private:
    uint32_t m_textureId;
    std::string m_filePath;
    int m_width, m_height, m_bitsPerPixel;
    uint32_t m_imageSlot;
    my_math::vec2 m_eachSpriteSize;
};
