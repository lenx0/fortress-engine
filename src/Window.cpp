#include "Window.h"
#include <iostream>

Window::Window(const std::string& title, unsigned int width, unsigned int height)
{
    Init(title, width, height);
}

Window::~Window()
{
    Shutdown();
}

void Window::Init(const std::string& title, unsigned int width, unsigned int height)
{
    m_Data.title = title;
    m_Data.width = width;
    m_Data.height = height;

    std::cout << "Creating window " << title << " (" << width << ", " << height << ")" << std::endl;

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the context current
    glfwMakeContextCurrent(m_Window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    // Set window user pointer for callbacks
    glfwSetWindowUserPointer(m_Window, &m_Data);

    // Note: Input callbacks will be set by Input::Initialize()
    // Only set essential window callbacks here
    
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;
        
        glViewport(0, 0, width, height);
        
        if (data.eventCallback)
            data.eventCallback();
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        if (data.eventCallback)
            data.eventCallback();
    });

    // Set initial viewport
    glViewport(0, 0, width, height);
    
    // Enable VSync
    glfwSwapInterval(1);
}

void Window::Shutdown()
{
    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}

void Window::OnUpdate()
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}