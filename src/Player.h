#pragma once

#include <glm/glm.hpp>

class Player
{
public:
    Player(const glm::vec2& startPosition = glm::vec2(0.0f, 0.0f));
    ~Player() = default;

    void Update(float deltaTime);
    void HandleInput(float deltaTime);
    void Move(const glm::vec2& direction, float deltaTime);
    
    const glm::vec2& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec2& position);
    
    bool IsMoving() const { return glm::length(m_Velocity) > 0.1f; }

private:
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    glm::vec2 m_InputDirection;
    
    float m_MoveSpeed;
    float m_Acceleration;
    float m_Friction;
};