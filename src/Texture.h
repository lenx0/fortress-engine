#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture();
    Texture(const std::string& filePath);
    ~Texture();

    // Delete copy constructor and assignment operator
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Move constructor and assignment operator
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    bool LoadFromFile(const std::string& filePath);
    bool LoadFromMemory(const unsigned char* data, int width, int height, int channels);
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    unsigned int GetID() const { return m_TextureID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    int GetChannels() const { return m_Channels; }

    bool IsValid() const { return m_TextureID != 0; }

private:
    void Release();

private:
    unsigned int m_TextureID;
    int m_Width;
    int m_Height;
    int m_Channels;
};