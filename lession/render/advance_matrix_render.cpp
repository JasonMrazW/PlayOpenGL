//
// Created by 王波 on 2022/6/12.
//

#include "advance_matrix_render.h"

void AdvanceMatrixRender::onDraw() {
    shader->use();
    //初始化单位矩阵
    glm::mat4 trans = glm::mat4(1.0f);

    float value = glfwGetTime();
    float x = (sin(value)/2.0f)+0.5f;
    float y = (cos(value)/2.0f)+0.5f;


    trans = glm::rotate(trans, (float )value, glm::vec3(1.0f, 0.0f, 0.0f));
    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));

    shader->setMatrix("transform", glm::value_ptr(trans));

    AdvanceTextureRender::onDraw();
}

void AdvanceMatrixRender::initShader() {
    shader = new Shader(vShaderPath, fShaderPath);
}
