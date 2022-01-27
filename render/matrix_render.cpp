//
// Created by bo on 2022/1/26.
//

#include "../headers/matrix_render.h"
#include <cmath>

void MatrixRender::onDraw() {
    shader->use();
    glm::mat4 trans = glm::mat4(1.0f);

    float value = glfwGetTime();
    float x = (sin(value)/2.0f)+0.5f;
    float y = (cos(value)/2.0f)+0.5f;

    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
    trans = glm::rotate(trans, (float )value, glm::vec3(1.0f, 0.0f, 0.0f));

    shader->setMatrix("transform", glm::value_ptr(trans));

    TextureRender::onDraw();
}
