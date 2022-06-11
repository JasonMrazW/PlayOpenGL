//
// Created by 王波 on 2022/6/11.
//

#include "triangle_render.h"


constexpr float TriangleRender::vertices[];

void TriangleRender::onInit() {
    shader = new Shader(vShaderPath, fShaderPath);

    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    //bind VAO
    glBindVertexArray(VAO);

    //bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //设置顶点属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float ), (void*)0);
    glEnableVertexAttribArray(1);

    //release
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void TriangleRender::onDraw() {
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

