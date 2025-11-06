#include "Application.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Camera.h"
#include "Player.h"
#include "Texture.h"
#include "Sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>

class IsometricGame : public Application
{
public:
    IsometricGame() = default;
    ~IsometricGame() = default;

protected:
    void OnInitialize() override
    {
        std::cout << "Isometric Game initialized!" << std::endl;
        
        // Create camera
        m_Camera = std::make_unique<Camera>(GetWindow()->GetWidth(), GetWindow()->GetHeight());
        m_Camera->SetPosition(glm::vec2(0.0f, 0.0f));
        m_Camera->SetZoom(2.0f);
        
        // Create player
        m_Player = std::make_unique<Player>(glm::vec2(0.0f, 0.0f));
        
        // Create a simple test texture for the player
        CreatePlayerTexture();
        
        ShowHelp();
    }

    void OnUpdate(float deltaTime) override
    {
        // Handle input
        HandleInput(deltaTime);
        
        // Update player
        m_Player->Update(deltaTime);
        
        // Update camera to follow player
        UpdateCamera(deltaTime);
    }

    void OnRender() override
    {
        // Clear with dark background
        GetRenderer()->Clear(glm::vec4(0.1f, 0.1f, 0.15f, 1.0f));
        
        // Set camera matrices
        glm::mat4 viewProjection = m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix();
        GetRenderer()->SetViewProjectionMatrix(viewProjection);
        
        // Render world
        RenderWorld();
        
        // Render player
        RenderPlayer();
    }

    void OnShutdown() override
    {
        std::cout << "Isometric game shutting down..." << std::endl;
    }

private:
    std::unique_ptr<Camera> m_Camera;
    std::unique_ptr<Player> m_Player;
    
    // Camera settings
    bool m_FollowPlayer = true;
    float m_CameraLerpSpeed = 5.0f;
    
    void HandleInput(float deltaTime)
    {
        // Close application
        if (Input::IsKeyPressed(Key::Escape))
        {
            std::cout << "ESC pressed - closing application" << std::endl;
            glfwSetWindowShouldClose(GetWindow()->GetNativeWindow(), GLFW_TRUE);
        }
        
        // Camera controls
        if (Input::IsKeyPressed(Key::C))
        {
            m_FollowPlayer = !m_FollowPlayer;
            std::cout << "Camera follow: " << (m_FollowPlayer ? "ON" : "OFF") << std::endl;
        }
        
        // Manual camera movement (when not following player)
        if (!m_FollowPlayer)
        {
            glm::vec2 cameraMove(0.0f);
            if (Input::IsKeyHeld(Key::Up)) cameraMove.y += 1.0f;
            if (Input::IsKeyHeld(Key::Down)) cameraMove.y -= 1.0f;
            if (Input::IsKeyHeld(Key::Left)) cameraMove.x -= 1.0f;
            if (Input::IsKeyHeld(Key::Right)) cameraMove.x += 1.0f;
            
            if (glm::length(cameraMove) > 0.0f)
            {
                m_Camera->Move(glm::normalize(cameraMove) * 5.0f * deltaTime);
            }
        }
        
        // Camera zoom
        float scroll = Input::GetScrollDelta();
        if (scroll != 0.0f)
        {
            m_Camera->Zoom(scroll * 0.1f);
            std::cout << "Camera zoom: " << m_Camera->GetZoom() << std::endl;
        }
        
        // Show help
        if (Input::IsKeyPressed(Key::H))
        {
            ShowHelp();
        }
    }
    
    void UpdateCamera(float deltaTime)
    {
        if (m_FollowPlayer)
        {
            // Convert player world position to isometric coordinates
            glm::vec2 playerIsoPos = m_Camera->WorldToIsometric(m_Player->GetPosition());
            
            // Smooth camera following
            glm::vec2 currentPos = m_Camera->GetPosition();
            glm::vec2 targetPos = playerIsoPos;
            glm::vec2 newPos = glm::mix(currentPos, targetPos, m_CameraLerpSpeed * deltaTime);
            
            m_Camera->SetPosition(newPos);
        }
    }
    
    void RenderWorld()
    {
        // Render a simple grid of floor tiles
        const int gridSize = 10;
        const float tileSize = 32.0f;
        
        for (int x = -gridSize; x <= gridSize; x++)
        {
            for (int y = -gridSize; y <= gridSize; y++)
            {
                // Convert world coordinates to isometric screen coordinates
                glm::vec2 worldPos(x, y);
                glm::vec2 isoPos = m_Camera->WorldToIsometric(worldPos);
                
                // Checkerboard pattern
                glm::vec4 tileColor = ((x + y) % 2 == 0) ? 
                    glm::vec4(0.3f, 0.6f, 0.3f, 1.0f) :  // Green
                    glm::vec4(0.2f, 0.5f, 0.2f, 1.0f);   // Darker green
                
                GetRenderer()->DrawQuad(isoPos, glm::vec2(tileSize, tileSize * 0.5f), tileColor);
            }
        }
    }
    
    void RenderPlayer()
    {
        // Convert player world position to isometric screen coordinates
        glm::vec2 playerIsoPos = m_Camera->WorldToIsometric(m_Player->GetPosition());
        
        // Get player sprite
        auto playerSprite = m_Player->GetSprite();
        if (playerSprite) {
            // Update sprite position to isometric coordinates
            playerSprite->SetPosition(playerIsoPos);
            
            // Render using sprite system
            GetRenderer()->DrawSprite(*playerSprite);
        }
    }
    
    void ShowHelp()
    {
        std::cout << "\n=== Isometric Game Controls ===" << std::endl;
        std::cout << "WASD    - Move player" << std::endl;
        std::cout << "C       - Toggle camera follow mode" << std::endl;
        std::cout << "Arrows  - Move camera (when not following)" << std::endl;
        std::cout << "Scroll  - Zoom camera" << std::endl;
        std::cout << "ESC     - Exit application" << std::endl;
        std::cout << "H       - Show this help" << std::endl;
        std::cout << "================================\n" << std::endl;
    }
    
    void CreatePlayerTexture()
    {
        // Create a simple 32x32 player texture procedurally
        const int size = 32;
        std::vector<unsigned char> pixels(size * size * 4); // RGBA
        
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                int index = (y * size + x) * 4;
                
                // Create a simple character shape
                bool isBody = false;
                bool isHead = false;
                
                // Head (circle in upper part)
                int headCenterX = size / 2;
                int headCenterY = size / 4;
                int headRadius = size / 6;
                float headDist = sqrt((x - headCenterX) * (x - headCenterX) + (y - headCenterY) * (y - headCenterY));
                isHead = headDist <= headRadius;
                
                // Body (rectangle in lower part)
                isBody = (x >= size/3 && x <= 2*size/3 && y >= size/2 && y <= 3*size/4);
                
                // Arms (small rectangles on sides)
                bool isArms = (y >= size/2 && y <= 2*size/3) && 
                             ((x >= size/6 && x <= size/3) || (x >= 2*size/3 && x <= 5*size/6));
                
                // Legs (rectangles at bottom)
                bool isLegs = (y >= 3*size/4 && y <= 7*size/8) && 
                             ((x >= size/3 && x <= size/2) || (x >= size/2 && x <= 2*size/3));
                
                if (isHead) {
                    // Pink/flesh color for head
                    pixels[index] = 255;     // R
                    pixels[index + 1] = 200; // G
                    pixels[index + 2] = 180; // B
                    pixels[index + 3] = 255; // A
                } else if (isBody || isArms) {
                    // Blue shirt
                    pixels[index] = 50;      // R
                    pixels[index + 1] = 100; // G
                    pixels[index + 2] = 200; // B
                    pixels[index + 3] = 255; // A
                } else if (isLegs) {
                    // Brown pants
                    pixels[index] = 139;     // R
                    pixels[index + 1] = 69;  // G
                    pixels[index + 2] = 19;  // B
                    pixels[index + 3] = 255; // A
                } else {
                    // Transparent background
                    pixels[index] = 0;       // R
                    pixels[index + 1] = 0;   // G
                    pixels[index + 2] = 0;   // B
                    pixels[index + 3] = 0;   // A (transparent)
                }
            }
        }
        
        // Create texture from pixel data
        auto playerTexture = std::make_shared<Texture>();
        if (playerTexture->LoadFromMemory(pixels.data(), size, size, 4)) {
            // Apply texture to player
            m_Player->SetTexture(playerTexture);
            std::cout << "Created procedural player texture (" << size << "x" << size << ")" << std::endl;
            std::cout << "Texture ID: " << playerTexture->GetID() << ", Valid: " << playerTexture->IsValid() << std::endl;
        } else {
            std::cerr << "Failed to create player texture" << std::endl;
        }
    }
};

int main()
{
    try
    {
        IsometricGame app;
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}