#include "Application.h"
#include "Input.h"
#include "KeyCodes.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

class GameApplication : public Application
{
public:
    GameApplication() = default;
    ~GameApplication() = default;

protected:
    void OnInitialize() override
    {
        std::cout << "Game initialized!" << std::endl;
        ShowHelp();
    }

    void OnUpdate(float deltaTime) override
    {
        // Handle input
        HandleInput(deltaTime);
        
        // Other game logic can go here
    }

    void OnRender() override
    {
        // Choose background color
        if (m_UseAnimatedBackground)
        {
            // Animated background
            static float totalTime = 0.0f;
            totalTime += 0.016f; // Approximate delta time
            glm::vec4 animatedColor;
            animatedColor.r = (std::sin(totalTime) + 1.0f) * 0.5f;
            animatedColor.g = (std::cos(totalTime * 0.7f) + 1.0f) * 0.5f;
            animatedColor.b = (std::sin(totalTime * 0.3f) + 1.0f) * 0.5f;
            animatedColor.a = 1.0f;
            GetRenderer()->Clear(animatedColor);
        }
        else
        {
            // Static color
            GetRenderer()->Clear(m_BackgroundColor);
        }
        
        // Draw triangle if visible
        if (m_ShowTriangle)
        {
            GetRenderer()->DrawTriangle();
        }
    }

    void OnShutdown() override
    {
        std::cout << "Game shutting down..." << std::endl;
    }

private:
    glm::vec4 m_BackgroundColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
    bool m_ShowTriangle = true;
    bool m_UseAnimatedBackground = true;
    float m_TriangleSpeed = 2.0f;
    
    void HandleInput(float deltaTime)
    {
        // Close application
        if (Input::IsKeyPressed(Key::Escape))
        {
            std::cout << "ESC pressed - closing application" << std::endl;
            glfwSetWindowShouldClose(GetWindow()->GetNativeWindow(), GLFW_TRUE);
        }
        
        // Toggle triangle visibility
        if (Input::IsKeyPressed(Key::Space))
        {
            m_ShowTriangle = !m_ShowTriangle;
            std::cout << "SPACE pressed - Triangle visibility: " << (m_ShowTriangle ? "ON" : "OFF") << std::endl;
        }
        
        // Change background colors with number keys
        if (Input::IsKeyPressed(Key::Num1))
        {
            m_BackgroundColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // Red
            m_UseAnimatedBackground = false;
            std::cout << "Key 1 pressed - Background: Red" << std::endl;
        }
        if (Input::IsKeyPressed(Key::Num2))
        {
            m_BackgroundColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); // Green
            m_UseAnimatedBackground = false;
            std::cout << "Key 2 pressed - Background: Green" << std::endl;
        }
        if (Input::IsKeyPressed(Key::Num3))
        {
            m_BackgroundColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); // Blue
            m_UseAnimatedBackground = false;
            std::cout << "Key 3 pressed - Background: Blue" << std::endl;
        }
        if (Input::IsKeyPressed(Key::Num0))
        {
            // Reset to animated background
            m_UseAnimatedBackground = true;
            std::cout << "Key 0 pressed - Background: Animated" << std::endl;
        }
        
        // Mouse input demonstration
        if (Input::IsMouseButtonPressed(MouseButton::Left))
        {
            glm::vec2 mousePos = Input::GetMousePosition();
            std::cout << "Left click at: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
        }
        
        if (Input::IsMouseButtonPressed(MouseButton::Right))
        {
            std::cout << "Right click detected!" << std::endl;
        }
        
        // Mouse scroll demonstration
        float scroll = Input::GetScrollDelta();
        if (scroll != 0.0f)
        {
            std::cout << "Mouse scroll: " << scroll << std::endl;
        }
        
        // Show help
        if (Input::IsKeyPressed(Key::H))
        {
            ShowHelp();
        }
    }
    
    void ShowHelp()
    {
        std::cout << "\n=== INPUT CONTROLS ===" << std::endl;
        std::cout << "ESC     - Close application" << std::endl;
        std::cout << "SPACE   - Toggle triangle visibility" << std::endl;
        std::cout << "1       - Red background" << std::endl;
        std::cout << "2       - Green background" << std::endl;
        std::cout << "3       - Blue background" << std::endl;
        std::cout << "0       - Animated background" << std::endl;
        std::cout << "H       - Show this help" << std::endl;
        std::cout << "Mouse   - Click and scroll for interaction" << std::endl;
        std::cout << "=====================\n" << std::endl;
    }
};

int main()
{
    try
    {
        GameApplication app;
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}