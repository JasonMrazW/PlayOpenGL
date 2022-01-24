//
// Created by bo on 2022/1/24.
//
#include "headers/triangle.h"
using namespace std;
constexpr float Triangle::vertices[];
constexpr unsigned int Triangle::indicators[];

void Triangle::onInit() {
    //create shader
    uint32_t vertexShader = GLUtils::createShader(GL_VERTEX_SHADER, vertex_shader_source);
    uint32_t fragmentShader = GLUtils::createShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    if (vertexShader < 0 || fragmentShader < 0) {
        return;
    }

    //create programmer
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int sucess;
    char info[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        cout << "create shader program failed.\n" << info << endl;
        return;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //----------------------------------------
    //create VBO
    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    uint32_t ebo_buffer = GLUtils::createBuffers();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicators), indicators, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void Triangle::onDraw() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);
}

void Triangle::onDestroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}