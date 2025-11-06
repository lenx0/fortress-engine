#include "Input.h"
#include <iostream>

// Static member definitions
GLFWwindow* Input::s_Window = nullptr;
std::array<KeyState, GLFW_KEY_LAST + 1> Input::s_KeyStates{};
std::array<KeyState, 8> Input::s_MouseButtonStates{};
glm::vec2 Input::s_MousePosition = glm::vec2(0.0f);
glm::vec2 Input::s_LastMousePosition = glm::vec2(0.0f);
glm::vec2 Input::s_MouseDelta = glm::vec2(0.0f);
float Input::s_ScrollDelta = 0.0f;
float Input::s_MouseSensitivity = 1.0f;
bool Input::s_FirstMouse = true;

void Input::Initialize(GLFWwindow* window)
{
    s_Window = window;
    
    std::cout << "Setting up input callbacks..." << std::endl;
    
    // Set GLFW callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    
    // Initialize mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    s_MousePosition = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
    s_LastMousePosition = s_MousePosition;
    
    std::cout << "Input system initialized successfully" << std::endl;
}

void Input::Update()
{
    // Update key states
    for (auto& keyState : s_KeyStates)
    {
        if (keyState == KeyState::Pressed)
            keyState = KeyState::Held;
        else if (keyState == KeyState::Released)
            keyState = KeyState::None; // Back to none after being released for one frame
    }
    
    // Update mouse button states
    for (auto& buttonState : s_MouseButtonStates)
    {
        if (buttonState == KeyState::Pressed)
            buttonState = KeyState::Held;
        else if (buttonState == KeyState::Released)
            buttonState = KeyState::None; // Back to none after being released for one frame
    }
    
    // Reset scroll delta
    s_ScrollDelta = 0.0f;
}

// Keyboard input
bool Input::IsKeyPressed(int keycode)
{
    if (keycode < 0 || keycode > GLFW_KEY_LAST) return false;
    return s_KeyStates[keycode] == KeyState::Pressed;
}

bool Input::IsKeyHeld(int keycode)
{
    if (keycode < 0 || keycode > GLFW_KEY_LAST) return false;
    KeyState state = s_KeyStates[keycode];
    return state == KeyState::Pressed || state == KeyState::Held;
}

bool Input::IsKeyReleased(int keycode)
{
    if (keycode < 0 || keycode > GLFW_KEY_LAST) return false;
    return s_KeyStates[keycode] == KeyState::Released;
}

KeyState Input::GetKeyState(int keycode)
{
    if (keycode < 0 || keycode > GLFW_KEY_LAST) return KeyState::None;
    return s_KeyStates[keycode];
}

// Mouse input
bool Input::IsMouseButtonPressed(MouseButton button)
{
    int index = static_cast<int>(button);
    if (index < 0 || index >= 8) return false;
    return s_MouseButtonStates[index] == KeyState::Pressed;
}

bool Input::IsMouseButtonHeld(MouseButton button)
{
    int index = static_cast<int>(button);
    if (index < 0 || index >= 8) return false;
    KeyState state = s_MouseButtonStates[index];
    return state == KeyState::Pressed || state == KeyState::Held;
}

bool Input::IsMouseButtonReleased(MouseButton button)
{
    int index = static_cast<int>(button);
    if (index < 0 || index >= 8) return false;
    return s_MouseButtonStates[index] == KeyState::Released;
}

KeyState Input::GetMouseButtonState(MouseButton button)
{
    int index = static_cast<int>(button);
    if (index < 0 || index >= 8) return KeyState::None;
    return s_MouseButtonStates[index];
}

// Mouse position
glm::vec2 Input::GetMousePosition()
{
    return s_MousePosition;
}

glm::vec2 Input::GetMouseDelta()
{
    return s_MouseDelta * s_MouseSensitivity;
}

float Input::GetScrollDelta()
{
    return s_ScrollDelta;
}

// Mouse settings
void Input::SetCursorMode(int mode)
{
    if (s_Window)
        glfwSetInputMode(s_Window, GLFW_CURSOR, mode);
}

void Input::SetMouseSensitivity(float sensitivity)
{
    s_MouseSensitivity = sensitivity;
}

// GLFW Callbacks
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key < 0 || key > GLFW_KEY_LAST) return;
    
    if (action == GLFW_PRESS)
        s_KeyStates[key] = KeyState::Pressed;
    else if (action == GLFW_RELEASE)
        s_KeyStates[key] = KeyState::Released;
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button < 0 || button >= 8) return;
    
    if (action == GLFW_PRESS)
        s_MouseButtonStates[button] = KeyState::Pressed;
    else if (action == GLFW_RELEASE)
        s_MouseButtonStates[button] = KeyState::Released;
}

void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    s_MousePosition = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
    
    if (s_FirstMouse)
    {
        s_LastMousePosition = s_MousePosition;
        s_FirstMouse = false;
    }
    
    s_MouseDelta = s_MousePosition - s_LastMousePosition;
    s_LastMousePosition = s_MousePosition;
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    s_ScrollDelta = static_cast<float>(yoffset);
}