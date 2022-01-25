//
// Created by bo on 2022/1/24.
//
#include <cmath>
#include "headers/shader_render.h"
constexpr float ShaderRender::vertices[];
constexpr float ShaderRender::verticesAndColors[];

const char *vShaderPath = "resources/shaders/vShader.vs";
const char *fShaderPath = "resources/shaders/fShader.fs";

void ShaderRender::onInit() {
    //create shaders
    shader = new Shader(vShaderPath, fShaderPath);

    //create VBO、VAO
    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAndColors), verticesAndColors, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float ), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float ), (void *)(3 * sizeof (float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ShaderRender::onDraw() {

//    float time = glfwGetTime();
//    float greenValue = (sin(time)/2.0f) + 0.5f; //-0.5~0.5===>0~1
//    int vertexColorLocation = glGetUniformLocation(shaderProgram, "renderColor");

    shader->use();
    //glUseProgram(shaderProgram);
    //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void ShaderRender::onDestroy() {
}

