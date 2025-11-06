#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite()
    : m_Texture(nullptr), 
      m_Position(0.0f, 0.0f), 
      m_Size(1.0f, 1.0f),
      m_Color(1.0f, 1.0f, 1.0f, 1.0f),
      m_UVMin(0.0f, 0.0f),
      m_UVMax(1.0f, 1.0f),
      m_Rotation(0.0f)
{
}

Sprite::Sprite(std::shared_ptr<Texture> texture)
    : m_Texture(texture),
      m_Position(0.0f, 0.0f),
      m_Size(1.0f, 1.0f),
      m_Color(1.0f, 1.0f, 1.0f, 1.0f),
      m_UVMin(0.0f, 0.0f),
      m_UVMax(1.0f, 1.0f),
      m_Rotation(0.0f)
{
    // Auto-size to texture dimensions if available
    if (texture && texture->IsValid())
    {
        m_Size = glm::vec2(static_cast<float>(texture->GetWidth()), 
                          static_cast<float>(texture->GetHeight()));
    }
}

Sprite::Sprite(std::shared_ptr<Texture> texture, const glm::vec2& position, const glm::vec2& size)
    : m_Texture(texture),
      m_Position(position),
      m_Size(size),
      m_Color(1.0f, 1.0f, 1.0f, 1.0f),
      m_UVMin(0.0f, 0.0f),
      m_UVMax(1.0f, 1.0f),
      m_Rotation(0.0f)
{
}

void Sprite::SetTextureCoords(const glm::vec2& uvMin, const glm::vec2& uvMax)
{
    m_UVMin = uvMin;
    m_UVMax = uvMax;
}