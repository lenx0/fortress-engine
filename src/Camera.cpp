#include "Camera.h"
#include <iostream>

Camera::Camera(float width, float height)
    : m_Position(0.0f, 0.0f), m_Zoom(1.0f), m_Width(width), m_Height(height)
{
    UpdateMatrices();
    std::cout << "Camera created: " << width << "x" << height << std::endl;
}

void Camera::SetPosition(const glm::vec2& position)
{
    m_Position = position;
    UpdateMatrices();
}

void Camera::Move(const glm::vec2& offset)
{
    m_Position += offset;
    UpdateMatrices();
}

void Camera::SetZoom(float zoom)
{
    m_Zoom = glm::clamp(zoom, 0.1f, 5.0f); // Limit zoom range
    UpdateMatrices();
}

void Camera::Zoom(float delta)
{
    SetZoom(m_Zoom + delta);
}

void Camera::UpdateMatrices()
{
    // Create orthographic projection matrix
    float halfWidth = (m_Width * 0.5f) / m_Zoom;
    float halfHeight = (m_Height * 0.5f) / m_Zoom;
    
    m_ProjectionMatrix = glm::ortho(
        -halfWidth, halfWidth,
        -halfHeight, halfHeight,
        -1.0f, 1.0f
    );

    // Create view matrix (camera transform)
    m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position.x, -m_Position.y, 0.0f));
    
    // Combine view and projection
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

glm::vec2 Camera::ScreenToWorld(const glm::vec2& screenPos) const
{
    // Convert screen coordinates to NDC (-1 to 1)
    float ndcX = (2.0f * screenPos.x) / m_Width - 1.0f;
    float ndcY = 1.0f - (2.0f * screenPos.y) / m_Height; // Flip Y

    // Convert NDC to world coordinates
    float halfWidth = (m_Width * 0.5f) / m_Zoom;
    float halfHeight = (m_Height * 0.5f) / m_Zoom;
    
    glm::vec2 worldPos;
    worldPos.x = ndcX * halfWidth + m_Position.x;
    worldPos.y = ndcY * halfHeight + m_Position.y;
    
    return worldPos;
}

glm::vec2 Camera::WorldToScreen(const glm::vec2& worldPos) const
{
    // Convert world to view space
    glm::vec2 viewPos = worldPos - m_Position;
    
    // Apply zoom and convert to screen coordinates
    float halfWidth = (m_Width * 0.5f) / m_Zoom;
    float halfHeight = (m_Height * 0.5f) / m_Zoom;
    
    float ndcX = viewPos.x / halfWidth;
    float ndcY = viewPos.y / halfHeight;
    
    glm::vec2 screenPos;
    screenPos.x = (ndcX + 1.0f) * m_Width * 0.5f;
    screenPos.y = (1.0f - ndcY) * m_Height * 0.5f; // Flip Y
    
    return screenPos;
}

glm::vec2 Camera::WorldToIsometric(const glm::vec2& worldPos) const
{
    // Convert 2D world coordinates to isometric screen coordinates
    glm::vec2 isoPos;
    isoPos.x = (worldPos.x - worldPos.y) * (TILE_WIDTH * 0.5f);
    isoPos.y = (worldPos.x + worldPos.y) * (TILE_HEIGHT * 0.5f);
    return isoPos;
}

glm::vec2 Camera::IsometricToWorld(const glm::vec2& isoPos) const
{
    // Convert isometric screen coordinates back to 2D world coordinates
    glm::vec2 worldPos;
    worldPos.x = (isoPos.x / (TILE_WIDTH * 0.5f) + isoPos.y / (TILE_HEIGHT * 0.5f)) * 0.5f;
    worldPos.y = (isoPos.y / (TILE_HEIGHT * 0.5f) - isoPos.x / (TILE_WIDTH * 0.5f)) * 0.5f;
    return worldPos;
}