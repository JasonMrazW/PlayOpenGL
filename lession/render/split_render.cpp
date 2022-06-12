//
// Created by 王波 on 2022/6/12.
//

#include "split_render.h"
constexpr float SplitRender::rectangle_vertices[];
constexpr uint32_t SplitRender::indices[];

void SplitRender::onInit() {
    shader = new Shader(vShaderPath, fShaderPath);

    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 5 *sizeof (float ), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 5 *sizeof (float ), (void *)(3*sizeof (float )));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    texture1 = GLUtils::createTexture("resources/imgs/container.jpg", GL_RGB);
    shader->use();
    shader->setFloat("texture1", 0);

}

void SplitRender::onDraw() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    shader->use();

    //初始化单位矩阵
    glm::mat4 trans = glm::mat4(1.0f);

    //left-top
    shader->setMatrix("transform", glm::value_ptr(trans));
    glBindVertexArray(VAO);
    shader->setFloat("xTex", 0.0f);
    shader->setFloat("yTex", 0.0f);
    shader->setMatrix("transform", glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //right-top
    //顶点平移一倍，仅x轴平移
    trans = glm::translate(trans, glm::vec3(1.0f,0.0f,0.0f));
    shader->setMatrix("transform", glm::value_ptr(trans));
    shader->setFloat("xTex", 0.5f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //left-bottom
    trans = glm::mat4(1.0f);
    //顶点平移一倍，仅y轴向下平移
    trans = glm::translate(trans, glm::vec3(0.0f,-1.0f,0.0f));
    shader->setMatrix("transform", glm::value_ptr(trans));
    shader->setFloat("xTex", 0.0f);
    shader->setFloat("yTex", -0.5f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //right-bottom
    //顶点平移一倍，仅x轴右平移
    trans = glm::translate(trans, glm::vec3(1.0f,0.0f,0.0f));
    shader->setMatrix("transform", glm::value_ptr(trans));
    shader->setFloat("xTex", 0.5f);
    shader->setFloat("yTex", 0.5f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void SplitRender::onDestroy() {

}
