#version 330 core
//vec表示向量，3表示维，vec3意思是3维向量（x,y,z)。从CPU传入的顶点数据存入该变量
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoord;

out vec3 outColor;
out vec2 outTex;

uniform mat4 transform = mat4(1.0f);

void main()
{
    gl_Position = transform * vec4(vertexPos, 1.0f);
    outColor = vertexColor;
    outTex = texCoord;
}
