#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoord;

out vec3 outColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
    outColor = vertexColor;
    TexCoord = texCoord;
}
