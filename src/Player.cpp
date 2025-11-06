#include "Player.h"
#include "Input.h"
#include "KeyCodes.h"
#include <iostream>
#include <algorithm>

Player::Player(const glm::vec2& startPosition)
    : m_Position(startPosition), m_Velocity(0.0f, 0.0f), m_InputDirection(0.0f, 0.0f)
{
    // Movement settings for smooth isometric movement
    m_MoveSpeed = 4.0f;      // Units per second
    m_Acceleration = 20.0f;  // How fast we reach max speed
    m_Friction = 15.0f;      // How fast we stop when no input
    
    std::cout << "Player created at position (" << m_Position.x << ", " << m_Position.y << ")" << std::endl;
}

void Player::Update(float deltaTime)
{
    HandleInput(deltaTime);
    
    // Apply acceleration or friction
    if (glm::length(m_InputDirection) > 0.0f)
    {
        // Normalize input direction and apply acceleration
        glm::vec2 targetVelocity = glm::normalize(m_InputDirection) * m_MoveSpeed;
        m_Velocity = glm::mix(m_Velocity, targetVelocity, m_Acceleration * deltaTime);
    }
    else
    {
        // Apply friction when no input
        m_Velocity = glm::mix(m_Velocity, glm::vec2(0.0f), m_Friction * deltaTime);
    }
    
    // Update position
    m_Position += m_Velocity * deltaTime;
    
    // Reset input direction for next frame
    m_InputDirection = glm::vec2(0.0f, 0.0f);
}

void Player::HandleInput(float deltaTime)
{
    glm::vec2 inputDir(0.0f, 0.0f);
    
    // Movimento isométrico: ajustar direções para perspectiva isométrica
    // Em jogos isométricos, as direções são rotacionadas 45 graus
    if (Input::IsKeyHeld(Key::W)) {
        // Cima isométrico = sudeste no mundo
        inputDir.x += 0.707f;  // +√2/2
        inputDir.y += 0.707f;  // +√2/2
    }
    if (Input::IsKeyHeld(Key::S)) {
        // Baixo isométrico = noroeste no mundo  
        inputDir.x -= 0.707f;  // -√2/2
        inputDir.y -= 0.707f;  // -√2/2
    }
    if (Input::IsKeyHeld(Key::A)) {
        // Esquerda isométrica = sudoeste no mundo
        inputDir.x -= 0.707f;  // -√2/2
        inputDir.y += 0.707f;  // +√2/2
    }
    if (Input::IsKeyHeld(Key::D)) {
        // Direita isométrica = nordeste no mundo
        inputDir.x += 0.707f;  // +√2/2
        inputDir.y -= 0.707f;  // -√2/2
    }
    
    // Normalizar para evitar movimento mais rápido nas diagonais
    if (glm::length(inputDir) > 0.0f) {
        inputDir = glm::normalize(inputDir);
    }
    
    m_InputDirection = inputDir;
    
    // Debug output when starting to move
    static bool wasMoving = false;
    bool isMoving = glm::length(inputDir) > 0.0f;
    if (isMoving && !wasMoving)
    {
        std::cout << "Player moving in direction (" << inputDir.x << ", " << inputDir.y << ")" << std::endl;
    }
    wasMoving = isMoving;
}

void Player::SetPosition(const glm::vec2& position)
{
    m_Position = position;
}

void Player::Move(const glm::vec2& direction, float deltaTime)
{
    m_Position += direction * m_MoveSpeed * deltaTime;
}