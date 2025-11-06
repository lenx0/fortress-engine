#version 330 core
in vec2 TexCoord;
in vec4 Color;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;

void main()
{
    if (u_UseTexture) {
        FragColor = texture(u_Texture, TexCoord) * Color;
    } else {
        FragColor = Color;
    }
}