#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(float width, float height);
    ~Camera() = default;

    // Camera controls
    void SetPosition(const glm::vec2& position);
    void Move(const glm::vec2& offset);
    void SetZoom(float zoom);
    void Zoom(float delta);

    // Matrix calculations
    void UpdateMatrices();
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    // Getters
    const glm::vec2& GetPosition() const { return m_Position; }
    float GetZoom() const { return m_Zoom; }
    float GetWidth() const { return m_Width; }
    float GetHeight() const { return m_Height; }

    // Screen/World coordinate conversion
    glm::vec2 ScreenToWorld(const glm::vec2& screenPos) const;
    glm::vec2 WorldToScreen(const glm::vec2& worldPos) const;

    // Isometric conversions
    glm::vec2 WorldToIsometric(const glm::vec2& worldPos) const;
    glm::vec2 IsometricToWorld(const glm::vec2& isoPos) const;

private:
    glm::vec2 m_Position;
    float m_Zoom;
    float m_Width, m_Height;

    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    // Isometric settings
    static constexpr float TILE_WIDTH = 64.0f;
    static constexpr float TILE_HEIGHT = 32.0f;
};