//
// Created by 王波 on 2022/6/11.
//

#include "triangle_render.h"


constexpr float TriangleRender::vertices[];
constexpr float TriangleRender::rectangle_vertices[];
constexpr int TriangleRender::indices[];

void TriangleRender::onInit() {
    shader = new Shader(vShaderPath, fShaderPath);

    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    //bind VAO
    glBindVertexArray(VAO);

    //bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //draw triangle
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //draw rectangle
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);

    //bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //设置顶点属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float ), (void*)0);
    glEnableVertexAttribArray(1);

    //release
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader->use();
}

void TriangleRender::onDraw() {

// draw triangle
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    //release
//    glBindVertexArray(0);

// draw rectangle
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

