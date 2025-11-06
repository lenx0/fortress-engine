#include "Renderer.h"
#include "Texture.h"
#include "Sprite.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

// Vertex shader source
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

// Fragment shader source
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

// Color vertex shader source (with MVP matrix)
const char* colorVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 uViewProjection;
uniform mat4 uModel;

void main()
{
    gl_Position = uViewProjection * uModel * vec4(aPos, 1.0);
}
)";

// Color fragment shader source
const char* colorFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

uniform vec4 uColor;

void main()
{
    FragColor = uColor;
}
)";

Renderer::Renderer()
    : m_DefaultShaderProgram(0), m_ColorShaderProgram(0), m_SpriteShaderProgram(0), m_TriangleVAO(0), m_TriangleVBO(0), 
      m_QuadVAO(0), m_QuadVBO(0), m_QuadEBO(0), m_SpriteVAO(0), m_SpriteVBO(0), m_SpriteEBO(0), 
      m_ViewProjectionLocation(-1), m_ModelLocation(-1), m_ColorLocation(-1)
{
}

Renderer::~Renderer()
{
    // Cleanup
    if (m_DefaultShaderProgram) glDeleteProgram(m_DefaultShaderProgram);
    if (m_ColorShaderProgram) glDeleteProgram(m_ColorShaderProgram);
    if (m_SpriteShaderProgram) glDeleteProgram(m_SpriteShaderProgram);
    if (m_TriangleVAO) glDeleteVertexArrays(1, &m_TriangleVAO);
    if (m_TriangleVBO) glDeleteBuffers(1, &m_TriangleVBO);
    if (m_QuadVAO) glDeleteVertexArrays(1, &m_QuadVAO);
    if (m_QuadVBO) glDeleteBuffers(1, &m_QuadVBO);
    if (m_QuadEBO) glDeleteBuffers(1, &m_QuadEBO);
    if (m_SpriteVAO) glDeleteVertexArrays(1, &m_SpriteVAO);
    if (m_SpriteVBO) glDeleteBuffers(1, &m_SpriteVBO);
    if (m_SpriteEBO) glDeleteBuffers(1, &m_SpriteEBO);
}

void Renderer::Initialize()
{
    std::cout << "Renderer: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    CreateDefaultShaders();
    
    // Create color shader
    m_ColorShaderProgram = CreateShader(colorVertexShaderSource, colorFragmentShaderSource);
    
    // Create sprite shader
    CreateSpriteShaders();
    
    // Get uniform locations
    m_ViewProjectionLocation = glGetUniformLocation(m_ColorShaderProgram, "uViewProjection");
    m_ModelLocation = glGetUniformLocation(m_ColorShaderProgram, "uModel");
    m_ColorLocation = glGetUniformLocation(m_ColorShaderProgram, "uColor");
    
    // Create triangle
    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    glGenVertexArrays(1, &m_TriangleVAO);
    glGenBuffers(1, &m_TriangleVBO);
    
    glBindVertexArray(m_TriangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_TriangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Create quad
    float quadVertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    
    unsigned int quadIndices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };
    
    glGenVertexArrays(1, &m_QuadVAO);
    glGenBuffers(1, &m_QuadVBO);
    glGenBuffers(1, &m_QuadEBO);
    
    glBindVertexArray(m_QuadVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
}

void Renderer::Clear(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void Renderer::DrawTriangle()
{
    glUseProgram(m_DefaultShaderProgram);
    glBindVertexArray(m_TriangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer::DrawQuad()
{
    glUseProgram(m_DefaultShaderProgram);
    glBindVertexArray(m_QuadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::SetViewProjectionMatrix(const glm::mat4& viewProjection)
{
    m_ViewProjectionMatrix = viewProjection;
    glUseProgram(m_ColorShaderProgram);
    glUniformMatrix4fv(m_ViewProjectionLocation, 1, GL_FALSE, &viewProjection[0][0]);
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    // Create model matrix for this quad
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
    
    // Use color shader
    glUseProgram(m_ColorShaderProgram);
    glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, &model[0][0]);
    glUniform4fv(m_ColorLocation, 1, &color[0]);
    
    // Draw quad
    glBindVertexArray(m_QuadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::CreateDefaultShaders()
{
    m_DefaultShaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);
}

unsigned int Renderer::CreateShader(const char* vertexSource, const char* fragmentSource)
{
    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    
    // Check vertex shader compilation
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    
    // Check fragment shader compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // Check program linking
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

void Renderer::CreateSpriteShaders()
{
    // Load sprite shaders from files
    m_SpriteShaderProgram = LoadShaderFromFile("shaders/sprite.vert", "shaders/sprite.frag");
    std::cout << "Sprite shader program ID: " << m_SpriteShaderProgram << std::endl;
    
    // Create sprite quad VAO/VBO/EBO
    // Sprite vertices with position, texture coordinates, and color
    float spriteVertices[] = {
        // positions        // texture coords   // colors (Y coords flipped to fix upside-down sprites)
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f,       1.0f, 1.0f, 1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f,       1.0f, 1.0f, 1.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,       1.0f, 1.0f, 1.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f,       1.0f, 1.0f, 1.0f, 1.0f  // top left
    };
    
    unsigned int spriteIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    glGenVertexArrays(1, &m_SpriteVAO);
    glGenBuffers(1, &m_SpriteVBO);
    glGenBuffers(1, &m_SpriteEBO);
    
    glBindVertexArray(m_SpriteVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_SpriteVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpriteEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(spriteIndices), spriteIndices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Color attribute
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
}

unsigned int Renderer::LoadShaderFromFile(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexSource = LoadShaderSource(vertexPath);
    std::string fragmentSource = LoadShaderSource(fragmentPath);
    
    if (vertexSource.empty() || fragmentSource.empty()) {
        std::cerr << "Failed to load shader files: " << vertexPath << ", " << fragmentPath << std::endl;
        return 0;
    }
    
    return CreateShader(vertexSource.c_str(), fragmentSource.c_str());
}

std::string Renderer::LoadShaderSource(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Renderer::DrawSprite(const Sprite& sprite)
{
    if (!sprite.HasTexture()) {
        // Draw as colored quad if no texture
        DrawQuad(sprite.GetPosition(), sprite.GetSize(), sprite.GetColor());
        return;
    }
    
    DrawSprite(sprite.GetTexture(), sprite.GetPosition(), sprite.GetSize(), sprite.GetColor());
}

void Renderer::DrawSprite(std::shared_ptr<Texture> texture, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    if (!texture || !texture->IsValid() || m_SpriteShaderProgram == 0) {
        // Draw as colored quad if no valid texture or shader
        std::cout << "Fallback to DrawQuad - Texture valid: " << (texture ? texture->IsValid() : false) 
                  << ", Shader ID: " << m_SpriteShaderProgram << std::endl;
        DrawQuad(position, size, color);
        return;
    }
    
    glUseProgram(m_SpriteShaderProgram);
    
    // Create model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
    
    // Set uniforms
    int mvpLocation = glGetUniformLocation(m_SpriteShaderProgram, "u_MVP");
    int textureLocation = glGetUniformLocation(m_SpriteShaderProgram, "u_Texture");
    int useTextureLocation = glGetUniformLocation(m_SpriteShaderProgram, "u_UseTexture");
    
    if (mvpLocation != -1) {
        glm::mat4 mvp = m_ViewProjectionMatrix * model;
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
    }
    
    if (textureLocation != -1) {
        glUniform1i(textureLocation, 0);
    }
    
    if (useTextureLocation != -1) {
        glUniform1i(useTextureLocation, texture && texture->IsValid() ? 1 : 0);
    }
    
    // Bind texture
    texture->Bind(0);
    
    // Draw sprite
    glBindVertexArray(m_SpriteVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    // Unbind texture
    texture->Unbind();
}