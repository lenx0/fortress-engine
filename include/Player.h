#pragma once

#include <glm/glm.hpp>

class Player
{
public:
    Player(const glm::vec2& startPosition = glm::vec2(0.0f, 0.0f));
    ~Player() = default;

    void Update(float deltaTime);
    void HandleInput(float deltaTime);

    // Movement
    void SetPosition(const glm::vec2& position);
    void Move(const glm::vec2& direction, float deltaTime);

    // Getters
    const glm::vec2& GetPosition() const { return m_Position; }
    const glm::vec2& GetWorldPosition() const { return m_Position; }
    const glm::vec2& GetVelocity() const { return m_Velocity; }
    bool IsMoving() const { return glm::length(m_Velocity) > 0.01f; }

private:
    glm::vec2 m_Position;        // World position (grid coordinates)
    glm::vec2 m_Velocity;        // Current velocity
    glm::vec2 m_InputDirection;  // Input direction this frame
    
    // Movement settings
    float m_MoveSpeed;
    float m_Acceleration;
    float m_Friction;
};