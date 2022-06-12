#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;
uniform mat4 transform;
uniform float xTex;
uniform float yTex;

void main()
{
    gl_Position = transform * vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
    TexCoord = vec2(texCoord.x + xTex, texCoord.y + yTex);
}
