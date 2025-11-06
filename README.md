# Fortress Engine

Uma engine de jogo isométrico 2D desenvolvida em C++ com OpenGL, sistema de input completo e renderização avançada.

## ✨ Funcionalidades

### 🎮 Jogo Isométrico 2D
- **Player controlável** com movimento em 8 direções
- **Sistema de coordenadas isométricas** (world-to-screen conversion)
- **Câmera isométrica** com seguimento suave do player
- **Grid de tiles isométrico** renderizado dinamicamente
- **Controles intuitivos** mapeados para perspectiva isométrica

### 📐 Sistema de Câmera Avançado
- **Projeção ortográfica** com zoom ajustável (0.1x - 5.0x)
- **Seguimento automático** do player com interpolação suave
- **Controle manual independente** da câmera
- **Conversão de coordenadas** mundo ↔ isométricas
- **Sistema de zoom** com mouse scroll

### 🎯 Sistema de Player
- **Física baseada** em aceleração e fricção
- **Movimento normalizado** para velocidade consistente
- **8 direções de movimento** (WASD + diagonais)
- **Feedback visual** de movimento com cores dinâmicas
- **Sistema de input responsivo** com detecção precisa

### 🎮 Sistema de Input Completo
- **Captura de teclado** com estados (Pressed, Held, Released)
- **Captura de mouse** (cliques, posição, scroll)
- **Callbacks GLFW** integrados
- **KeyCodes** amigáveis para fácil uso

### 🎨 Sistema de Renderização
- **OpenGL 3.3 Core Profile**
- **Sistema de matrizes MVP** (Model-View-Projection)
- **Renderização de quads coloridos** com transformações
- **Grid de tiles** com padrão xadrez visual
- **Sistema de cores** dinâmico baseado em estados

### 🏗️ Arquitetura da Engine
- **Classe Application** - Game loop principal
- **Classe Window** - Gerenciamento de janela GLFW
- **Classe Renderer** - Sistema de renderização OpenGL avançado
- **Classe Input** - Sistema de entrada completo
- **Classe Camera** - Sistema de câmera isométrica
- **Classe Player** - Entidade de jogador com física

## 🎯 Controles do Jogo Isométrico

### 🚶 Movimento do Player
| Tecla | Direção |
|-------|---------|
| **W** | Cima (sudeste no mundo) |
| **S** | Baixo (noroeste no mundo) |
| **A** | Esquerda (sudoeste no mundo) |
| **D** | Direita (nordeste no mundo) |

### 📷 Controles da Câmera
| Tecla/Ação | Função |
|------------|--------|
| **C** | Toggle modo seguimento da câmera |
| **↑↓←→** | Controle manual da câmera |
| **Mouse Scroll** | Zoom da câmera |

### 🎮 Controles Gerais
| Tecla | Ação |
|-------|------|
| **ESC** | Fechar aplicação |
| **H** | Mostrar ajuda no console |

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
│   ├── main.cpp        # Jogo isométrico principal
│   ├── Application.cpp # Engine principal
│   ├── Window.cpp      # Gerenciamento de janela
│   ├── Renderer.cpp    # Sistema de renderização
│   ├── Input.cpp       # Sistema de input
│   ├── Camera.cpp      # Sistema de câmera isométrica
│   ├── Camera.h        # Header da câmera
│   ├── Player.cpp      # Sistema de player
│   └── Player.h        # Header do player
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

### 🎮 Expansões do Jogo Isométrico
- [ ] **Sistema de Sprites** - Sprites 2D com animações para personagem
- [ ] **Sistema de Texturas** - Carregamento de texturas para tiles e objetos
- [ ] **Z-Order/Depth Sorting** - Renderização em ordem correta (frente/trás)
- [ ] **Colisões com Tiles** - Sistema básico de colisão para tiles sólidos
- [ ] **Sistema de Mapa** - Carregamento de mapas de arquivos
- [ ] **Objetos Interativos** - NPCs, itens, portas, etc.

### 🏗️ Melhorias da Engine
- [ ] **Sistema de Entidades (ECS)** - GameObject/Component architecture
- [ ] **Sistema de Áudio** - Sons e música
- [ ] **Sistema de UI** - Interface de usuário 2D
- [ ] **Sistema de Animações** - Animador 2D para sprites
- [ ] **Sistema de Partículas** - Efeitos visuais
- [ ] **Sistema de Save/Load** - Persistência de dados

## 📝 Logs de Desenvolvimento

### v0.3.0 - Jogo Isométrico 2D Completo
- ✅ **Sistema de Câmera Isométrica** - Projeção ortográfica com zoom e seguimento
- ✅ **Player Controlável** - Movimento em 8 direções com física suave
- ✅ **Coordenadas Isométricas** - Conversão mundo ↔ tela para perspectiva correta
- ✅ **Controles WASD** - Mapeamento correto para direções isométricas
- ✅ **Grid de Tiles** - Renderização de mundo isométrico com padrão visual
- ✅ **Sistema MVP** - Matrizes Model-View-Projection para transformações
- ✅ **Renderização Avançada** - Quads coloridos com transformações matemáticas
- ✅ **Feedback Visual** - Cores dinâmicas baseadas no estado do player

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

---

🎮 **A Fortress Engine agora é um jogo isométrico 2D totalmente funcional!**

Experimente os controles WASD para mover o personagem, use C para alternar o modo da câmera, e scroll do mouse para zoom. O jogo demonstra todos os sistemas fundamentais de um jogo isométrico moderno!