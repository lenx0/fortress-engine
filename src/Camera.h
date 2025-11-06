#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(float windowWidth, float windowHeight);
    ~Camera() = default;

    // Camera transform methods
    void SetPosition(const glm::vec2& position);
    void Move(const glm::vec2& offset);
    const glm::vec2& GetPosition() const { return m_Position; }

    // Camera zoom
    void SetZoom(float zoom);
    void Zoom(float delta);
    float GetZoom() const { return m_Zoom; }

    // Matrix getters
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    
    // Coordinate conversion for isometric view
    glm::vec2 WorldToIsometric(const glm::vec2& worldPos) const;
    glm::vec2 IsometricToWorld(const glm::vec2& isoPos) const;

private:
    void UpdateMatrices();

private:
    glm::vec2 m_Position;
    float m_Zoom;
    float m_Width, m_Height;
    
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
};