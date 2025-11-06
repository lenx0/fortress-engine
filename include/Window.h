#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

class Window
{
public:
    using EventCallback = std::function<void()>;

    struct WindowData
    {
        std::string title;
        unsigned int width, height;
        EventCallback eventCallback;
    };

    Window(const std::string& title = "Game Engine", unsigned int width = 1280, unsigned int height = 720);
    ~Window();

    void OnUpdate();
    void SetEventCallback(const EventCallback& callback) { m_Data.eventCallback = callback; }

    inline unsigned int GetWidth() const { return m_Data.width; }
    inline unsigned int GetHeight() const { return m_Data.height; }
    
    inline GLFWwindow* GetNativeWindow() const { return m_Window; }
    
    bool ShouldClose() const;
    void SwapBuffers();

private:
    void Init(const std::string& title, unsigned int width, unsigned int height);
    void Shutdown();

    GLFWwindow* m_Window;
    WindowData m_Data;
};