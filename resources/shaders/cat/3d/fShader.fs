#version 330 core
in vec3 outColor;
in vec2 outTex;

out vec4 FragColor;
uniform sampler2D textureBody;

void main()
{
//     FragColor = texture(textureBody, outTex);
FragColor = vec4(outColor, 1.0f);
}