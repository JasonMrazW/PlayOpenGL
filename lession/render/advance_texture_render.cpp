//
// Created by 王波 on 2022/6/12.
//

#include "advance_texture_render.h"

constexpr float AdvanceTextureRender::verticesAndColors[];
constexpr float AdvanceTextureRender::rectangle_vertices[];
constexpr uint32_t AdvanceTextureRender::indices[];

void AdvanceTextureRender::onInit() {
    initShader();

    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAndColors), verticesAndColors, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float ), (void *)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float ), (void *)(3 * sizeof (float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void *)(6 * sizeof (float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //create texture
    texture1 = GLUtils::createTexture("resources/imgs/container.jpg", GL_RGB);
    texture2 = GLUtils::createTexture("resources/imgs/awesomeface.png", GL_RGBA);
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
    shader->setFloat("mixerValue", 0.0f);
}

void AdvanceTextureRender::onDraw() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void AdvanceTextureRender::onDestroy() {

}

void AdvanceTextureRender::initShader() {
    shader = new Shader(vShaderPath, fShaderPath);
}
