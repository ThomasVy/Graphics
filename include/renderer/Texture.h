#pragma once
#include <string>

class Texture
{
public:
    Texture(std::string path, uint32_t slot);
    Texture(std::string path1, std::string path2);
    ~Texture();
    Texture(const Texture&) = delete;
    int GetWidth() const {return m_width;}
    int GetHeight() const { return m_height; }
    inline uint32_t GetImageSlot() const {return m_imageSlot;}
    
private:
    uint32_t m_textureId;
    std::string m_filePath;
    int m_width, m_height, m_bitsPerPixel;
    uint32_t m_imageSlot;
};
