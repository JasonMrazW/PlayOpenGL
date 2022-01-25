#version 330 core
in vec3 renderColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(renderColor, 1.0f);
}