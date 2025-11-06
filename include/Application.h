#pragma once

#include "Window.h"
#include "Renderer.h"
#include <memory>

class Application
{
public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent();

protected:
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnInitialize() {}
    virtual void OnShutdown() {}

    // Protected getters for derived classes
    Window* GetWindow() { return m_Window.get(); }
    Renderer* GetRenderer() { return m_Renderer.get(); }

private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;
    bool m_Running;
    float m_LastFrameTime;
};