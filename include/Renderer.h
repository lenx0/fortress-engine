#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Initialize();
    void Clear(const glm::vec4& color = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    void SetViewport(int x, int y, int width, int height);
    
    // Matrix operations
    void SetViewProjectionMatrix(const glm::mat4& viewProjection);
    
    // Render primitives
    void DrawTriangle();
    void DrawQuad();
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));

private:
    void CreateDefaultShaders();
    unsigned int CreateShader(const char* vertexSource, const char* fragmentSource);
    
    unsigned int m_DefaultShaderProgram;
    unsigned int m_ColorShaderProgram;
    unsigned int m_TriangleVAO, m_TriangleVBO;
    unsigned int m_QuadVAO, m_QuadVBO, m_QuadEBO;
    
    // Uniform locations
    int m_ViewProjectionLocation;
    int m_ModelLocation;
    int m_ColorLocation;
};