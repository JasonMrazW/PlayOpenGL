#version 330 core
//vec表示向量，3表示维，vec3意思是3维向量（x,y,z)。从CPU传入的顶点数据存入该变量
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;

out vec3 outColor;

void main()
{
    gl_Position = vec4(vertexPos, 1.0f);
    outColor = vertexColor;
}
