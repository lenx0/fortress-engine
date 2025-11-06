#include "Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
    : m_TextureID(0), m_Width(0), m_Height(0), m_Channels(0)
{
}

Texture::Texture(const std::string& filePath)
    : m_TextureID(0), m_Width(0), m_Height(0), m_Channels(0)
{
    LoadFromFile(filePath);
}

Texture::~Texture()
{
    Release();
}

Texture::Texture(Texture&& other) noexcept
    : m_TextureID(other.m_TextureID), m_Width(other.m_Width), 
      m_Height(other.m_Height), m_Channels(other.m_Channels)
{
    other.m_TextureID = 0;
    other.m_Width = 0;
    other.m_Height = 0;
    other.m_Channels = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other)
    {
        Release();
        
        m_TextureID = other.m_TextureID;
        m_Width = other.m_Width;
        m_Height = other.m_Height;
        m_Channels = other.m_Channels;
        
        other.m_TextureID = 0;
        other.m_Width = 0;
        other.m_Height = 0;
        other.m_Channels = 0;
    }
    return *this;
}

bool Texture::LoadFromFile(const std::string& filePath)
{
    // Release any existing texture
    Release();
    
    // Flip images vertically (OpenGL expects bottom-left origin)
    stbi_set_flip_vertically_on_load(true);
    
    // Load image data
    unsigned char* data = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);
    if (!data)
    {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
        return false;
    }
    
    // Generate OpenGL texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Determine format based on channels
    GLenum format = GL_RGB;
    if (m_Channels == 1)
        format = GL_RED;
    else if (m_Channels == 3)
        format = GL_RGB;
    else if (m_Channels == 4)
        format = GL_RGBA;
    
    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Cleanup
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    std::cout << "Texture loaded successfully: " << filePath 
              << " (" << m_Width << "x" << m_Height << ", " << m_Channels << " channels)" << std::endl;
    
    return true;
}

bool Texture::LoadFromMemory(const unsigned char* data, int width, int height, int channels)
{
    // Release any existing texture
    Release();
    
    if (!data || width <= 0 || height <= 0 || channels <= 0) {
        std::cerr << "Invalid texture data provided" << std::endl;
        return false;
    }
    
    m_Width = width;
    m_Height = height;
    m_Channels = channels;
    
    // Generate OpenGL texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // Determine format based on channels
    GLenum format = GL_RGB;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;
    
    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    
    // Cleanup
    glBindTexture(GL_TEXTURE_2D, 0);
    
    std::cout << "Texture created from memory: " 
              << width << "x" << height << ", " << channels << " channels" << std::endl;
    
    return true;
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Release()
{
    if (m_TextureID != 0)
    {
        glDeleteTextures(1, &m_TextureID);
        m_TextureID = 0;
        m_Width = 0;
        m_Height = 0;
        m_Channels = 0;
    }
}