#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>

Application::Application()
    : m_Running(true), m_LastFrameTime(0.0f)
{
    // Create window
    m_Window = std::make_unique<Window>("Game Engine", 1280, 720);
    
    // Set event callback
    m_Window->SetEventCallback([this]() { OnEvent(); });
    
    // Create renderer
    m_Renderer = std::make_unique<Renderer>();
    m_Renderer->Initialize();
    
    // Initialize input system
    Input::Initialize(m_Window->GetNativeWindow());
    
    std::cout << "Application initialized successfully!" << std::endl;
}

Application::~Application()
{
    OnShutdown();
}

void Application::Run()
{
    OnInitialize();
    
    while (m_Running && !m_Window->ShouldClose())
    {
        // Calculate delta time
        float time = static_cast<float>(glfwGetTime());
        float deltaTime = time - m_LastFrameTime;
        m_LastFrameTime = time;
        
        // Update
        m_Window->OnUpdate();
        OnUpdate(deltaTime);  // Handle input BEFORE updating states
        Input::Update();      // Update states AFTER handling input
        
        // Render
        m_Renderer->Clear();
        OnRender();
        m_Window->SwapBuffers();
    }
}

void Application::OnEvent()
{
    // Handle window events
    if (m_Window->ShouldClose())
    {
        m_Running = false;
    }
}