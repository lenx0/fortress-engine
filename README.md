# Game Engine

Uma engine de jogo desenvolvida em C++ com OpenGL, sistema de input e renderização básica.

## ✨ Funcionalidades

### 🎮 Sistema de Input Completo
- **Captura de teclado** com estados (Pressed, Held, Released)
- **Captura de mouse** (cliques, posição, scroll)
- **Callbacks GLFW** integrados
- **KeyCodes** amigáveis para fácil uso

### 🎨 Sistema de Renderização
- **OpenGL 3.3 Core Profile**
- **Shaders básicos** (vertex/fragment)
- **Primitivas geométricas** (triângulos, quads)
- **Sistema de cores** animado e estático

### 🏗️ Arquitetura da Engine
- **Classe Application** - Game loop principal
- **Classe Window** - Gerenciamento de janela GLFW
- **Classe Renderer** - Sistema de renderização OpenGL
- **Classe Input** - Sistema de entrada completo

## 🎯 Controles

| Tecla | Ação |
|-------|------|
| **ESC** | Fechar aplicação |
| **SPACE** | Alternar visibilidade do triângulo |
| **1** | Background vermelho |
| **2** | Background verde |
| **3** | Background azul |
| **0** | Background animado (padrão) |
| **H** | Mostrar ajuda |
| **Mouse** | Cliques e scroll detectados |

## 🛠️ Dependências

- **CMake 3.16+**
- **Visual Studio 2019+** (Windows)
- **OpenGL 3.3+**
- **GLFW3** - Criação de janela e contexto
- **GLAD** - Carregamento de funções OpenGL
- **GLM** - Biblioteca de matemática 3D

## 📦 Setup no Windows

1. **Instalar vcpkg:**
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

2. **Instalar dependências:**
```bash
.\vcpkg install glfw3:x64-windows
.\vcpkg install glad:x64-windows
.\vcpkg install glm:x64-windows
```

3. **Configurar projeto:**
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
```

4. **Compilar:**
```bash
cmake --build . --config Release
```

5. **Executar:**
```bash
.\bin\Release\GameEngine.exe
```

## 📁 Estrutura do Projeto

```
GameEngine/
├── src/                 # Código fonte
│   ├── main.cpp        # Aplicação demo
│   ├── Application.cpp # Engine principal
│   ├── Window.cpp      # Gerenciamento de janela
│   ├── Renderer.cpp    # Sistema de renderização
│   └── Input.cpp       # Sistema de input
├── include/            # Headers
│   ├── Application.h
│   ├── Window.h
│   ├── Renderer.h
│   ├── Input.h
│   └── KeyCodes.h     # Definições de teclas
├── shaders/           # Shaders GLSL
│   ├── basic.vert
│   └── basic.frag
├── .vscode/           # Configuração VS Code
├── CMakeLists.txt     # Build system
└── README.md          # Documentação
```

## 🚀 Próximos Passos

- [ ] **Câmera 3D** - Sistema de visualização 3D com controles
- [ ] **Sistema de Texturas** - Carregamento e aplicação de imagens
- [ ] **Sistema de Entidades** - GameObject/Component architecture
- [ ] **Modelos 3D** - Carregamento de meshes (.obj)
- [ ] **Sistema de Física** - Colisões e movimento
- [ ] **Sistema de Áudio** - Sons e música
- [ ] **Iluminação** - Luzes dinâmicas
- [ ] **Material System** - Shaders avançados PBR

## 📝 Logs de Desenvolvimento

### v0.2.0 - Sistema de Input
- ✅ Sistema completo de captura de teclado e mouse
- ✅ Estados de teclas (Pressed/Held/Released)
- ✅ Callbacks GLFW integrados
- ✅ Controles interativos (cores, visibilidade)
- ✅ KeyCodes amigáveis
- ✅ Correção de timing no game loop

### v0.1.0 - Base da Engine
- ✅ Estrutura básica da engine
- ✅ Sistema de renderização OpenGL
- ✅ Game loop com delta time
- ✅ Gerenciamento de janela GLFW
- ✅ Build system CMake com vcpkg