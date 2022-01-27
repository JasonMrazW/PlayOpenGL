#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 colorPos;
layout (location = 2) in vec2 texCoord;
out vec3 renderColor;
out vec2 TexCoord;

uniform mat4 transform = mat4(1.0f);

void main()
{
    gl_Position = transform * vec4(vertexPos, 1.0f);
    renderColor = colorPos;
    TexCoord = texCoord;
}
