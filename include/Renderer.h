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
    
    // Render primitives
    void DrawTriangle();
    void DrawQuad();

private:
    void CreateDefaultShaders();
    unsigned int CreateShader(const char* vertexSource, const char* fragmentSource);
    
    unsigned int m_DefaultShaderProgram;
    unsigned int m_TriangleVAO, m_TriangleVBO;
    unsigned int m_QuadVAO, m_QuadVBO, m_QuadEBO;
};