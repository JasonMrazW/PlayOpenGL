#version 330 core
layout (location = 1) in vec3 vertexPos;

void main()
{
    gl_Position = vec4(vertexPos, 1.0f);
}
