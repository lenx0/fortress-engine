# Game Engine

Uma engine de jogo simples desenvolvida em C++ com OpenGL.

## Dependências

- CMake 3.16+
- Visual Studio 2019+ (no Windows)
- OpenGL
- GLFW3
- GLAD

## Setup no Windows

1. Instale o vcpkg:
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

2. Instale as dependências:
```bash
.\vcpkg install glfw3:x64-windows
.\vcpkg install glad:x64-windows
.\vcpkg install glm:x64-windows
```

3. Configure o projeto:
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
```

4. Compile:
```bash
cmake --build . --config Release
```

## Estrutura do Projeto

- `src/` - Código fonte
- `include/` - Headers
- `shaders/` - Shaders GLSL
- `libs/` - Bibliotecas externas