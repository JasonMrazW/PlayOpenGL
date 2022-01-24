//
// Created by bo on 2022/1/24.
//
#include "headers/shaders.h"
constexpr float Shaders::vertices[];

void Shaders::onInit() {
    //create shaders
    uint32_t vertex_shader = GLUtils::createShader(GL_VERTEX_SHADER, vertex_shader_source);
    uint32_t fragment_shader = GLUtils::createShader(GL_FRAGMENT_SHADER, fragment_shader_source);

    if (vertex_shader <0 || fragment_shader <0) {
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);

    int sucess;
    char info[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        cout << "create shader program failed.\n" << info << endl;
        return;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    //create VBO、VAO
    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float ), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Shaders::onDraw() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Shaders::onDestroy() {
}

