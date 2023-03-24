#pragma once
#include <string>

class Texture
{
public:
    Texture(std::string path);
    ~Texture();

    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

    int GetWidth() const {return m_width;}
    int GetHeight() const { return m_height; }

private:
    uint32_t m_textureId;
    std::string m_filePath;
    uint8_t* m_localBuffer;
    int m_width, m_height, m_bitsPerPixel;
};
