#pragma once

#include <glm/glm.hpp>
#include <memory>

class Texture;

class Sprite
{
public:
    Sprite();
    Sprite(std::shared_ptr<Texture> texture);
    Sprite(std::shared_ptr<Texture> texture, const glm::vec2& position, const glm::vec2& size);
    ~Sprite() = default;

    // Position and size
    void SetPosition(const glm::vec2& position) { m_Position = position; }
    void SetSize(const glm::vec2& size) { m_Size = size; }
    const glm::vec2& GetPosition() const { return m_Position; }
    const glm::vec2& GetSize() const { return m_Size; }

    // Texture
    void SetTexture(std::shared_ptr<Texture> texture) { m_Texture = texture; }
    std::shared_ptr<Texture> GetTexture() const { return m_Texture; }

    // Color tint (multiplied with texture)
    void SetColor(const glm::vec4& color) { m_Color = color; }
    const glm::vec4& GetColor() const { return m_Color; }

    // Texture coordinates (UV mapping)
    void SetTextureCoords(const glm::vec2& uvMin, const glm::vec2& uvMax);
    const glm::vec2& GetUVMin() const { return m_UVMin; }
    const glm::vec2& GetUVMax() const { return m_UVMax; }

    // Rotation (in radians)
    void SetRotation(float rotation) { m_Rotation = rotation; }
    float GetRotation() const { return m_Rotation; }

    // Utility
    bool HasTexture() const { return m_Texture != nullptr; }

private:
    std::shared_ptr<Texture> m_Texture;
    glm::vec2 m_Position;
    glm::vec2 m_Size;
    glm::vec4 m_Color;
    glm::vec2 m_UVMin;
    glm::vec2 m_UVMax;
    float m_Rotation;
};