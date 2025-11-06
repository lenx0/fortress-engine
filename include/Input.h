#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>

enum class KeyState
{
    None = 0,
    Pressed = 1,
    Held = 2,
    Released = 3
};

enum class MouseButton
{
    Left = 0,
    Right = 1,
    Middle = 2,
    Button4 = 3,
    Button5 = 4,
    Button6 = 5,
    Button7 = 6,
    Button8 = 7
};

class Input
{
public:
    static void Initialize(GLFWwindow* window);
    static void Update();
    
    // Keyboard input
    static bool IsKeyPressed(int keycode);
    static bool IsKeyHeld(int keycode);
    static bool IsKeyReleased(int keycode);
    static KeyState GetKeyState(int keycode);
    
    // Mouse input
    static bool IsMouseButtonPressed(MouseButton button);
    static bool IsMouseButtonHeld(MouseButton button);
    static bool IsMouseButtonReleased(MouseButton button);
    static KeyState GetMouseButtonState(MouseButton button);
    
    // Mouse position
    static glm::vec2 GetMousePosition();
    static glm::vec2 GetMouseDelta();
    static float GetScrollDelta();
    
    // Mouse settings
    static void SetCursorMode(int mode); // GLFW_CURSOR_NORMAL, GLFW_CURSOR_HIDDEN, GLFW_CURSOR_DISABLED
    static void SetMouseSensitivity(float sensitivity);

private:
    static GLFWwindow* s_Window;
    static std::array<KeyState, GLFW_KEY_LAST + 1> s_KeyStates;
    static std::array<KeyState, 8> s_MouseButtonStates;
    
    static glm::vec2 s_MousePosition;
    static glm::vec2 s_LastMousePosition;
    static glm::vec2 s_MouseDelta;
    static float s_ScrollDelta;
    static float s_MouseSensitivity;
    static bool s_FirstMouse;
    
    // GLFW Callbacks
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};