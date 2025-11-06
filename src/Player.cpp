#include "Player.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>
#include <algorithm>

Player::Player(const glm::vec2& startPosition)
    : m_Position(startPosition), m_Velocity(0.0f, 0.0f), m_InputDirection(0.0f, 0.0f)
{
    // Movement settings for smooth isometric movement
    m_MoveSpeed = 4.0f;      // Units per second
    m_Acceleration = 20.0f;  // How fast we reach max speed
    m_Friction = 15.0f;      // How fast we stop when no input
    
    // Create default sprite (will use colored quad if no texture)
    m_Sprite = std::make_shared<Sprite>();
    m_Sprite->SetPosition(m_Position);
    m_Sprite->SetSize(glm::vec2(24.0f, 24.0f));
    m_Sprite->SetColor(glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)); // Red color
    
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
    
    // Update sprite position and color based on movement
    if (m_Sprite) {
        m_Sprite->SetPosition(m_Position);
        
        // Change color based on movement
        if (IsMoving()) {
            m_Sprite->SetColor(glm::vec4(1.0f, 0.3f, 0.3f, 1.0f)); // Bright red when moving
        } else {
            m_Sprite->SetColor(glm::vec4(0.8f, 0.2f, 0.2f, 1.0f)); // Darker red when idle
        }
    }
    
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
    if (m_Sprite) {
        m_Sprite->SetPosition(position);
    }
}

void Player::Move(const glm::vec2& direction, float deltaTime)
{
    m_Position += direction * m_MoveSpeed * deltaTime;
    if (m_Sprite) {
        m_Sprite->SetPosition(m_Position);
    }
}

void Player::SetTexture(std::shared_ptr<Texture> texture)
{
    if (m_Sprite) {
        m_Sprite->SetTexture(texture);
    }
}