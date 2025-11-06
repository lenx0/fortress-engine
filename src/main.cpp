#include "Application.h"
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
    }

    void OnUpdate(float deltaTime) override
    {
        // Update game logic here
        static float totalTime = 0.0f;
        totalTime += deltaTime;
        
        // Change background color over time
        m_BackgroundColor.r = (std::sin(totalTime) + 1.0f) * 0.5f;
        m_BackgroundColor.g = (std::cos(totalTime * 0.7f) + 1.0f) * 0.5f;
        m_BackgroundColor.b = (std::sin(totalTime * 0.3f) + 1.0f) * 0.5f;
    }

    void OnRender() override
    {
        // Set background color
        GetRenderer()->Clear(m_BackgroundColor);
        
        // Draw a triangle in the center
        GetRenderer()->DrawTriangle();
    }

    void OnShutdown() override
    {
        std::cout << "Game shutting down..." << std::endl;
    }

private:
    glm::vec4 m_BackgroundColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
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