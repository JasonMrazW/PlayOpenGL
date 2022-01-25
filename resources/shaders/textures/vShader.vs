#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 colorPos;
layout (location = 2) in vec2 texCoord;
out vec3 renderColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(vertexPos, 1.0f);
    renderColor = colorPos;
    TexCoord = texCoord;
}
