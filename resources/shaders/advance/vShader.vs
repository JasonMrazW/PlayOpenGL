#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;

out vec3 outColor;
void main()
{
    gl_Position = vec4(vertexPos, 1.0f);
    outColor = vertexColor;
}
