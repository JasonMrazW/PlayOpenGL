//
// Created by 王波 on 2022/6/12.
//

#ifndef PLAYOPENGL_SPLIT_RENDER_H
#define PLAYOPENGL_SPLIT_RENDER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../../headers/IRender.h"

class SplitRender: public IRender {
public:
    SplitRender():IRender() {}
    ~SplitRender() = default;

protected:
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    uint32_t texture1;

    const char *vShaderPath = "resources/shaders/split/vShader.vs";
    const char *fShaderPath = "resources/shaders/split/fShader.fs";

    constexpr static float rectangle_vertices[] = {
            0.0f,  1.0f, 0.0f,  0.5f, 1.0f,// top right
            0.0f, 0.0f, 0.0f,  0.5f, 0.5f,// bottom right
            -1.0f, 0.0f, 0.0f,  0.0f, 0.5f,// bottom left
            -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,// top left
    };

    constexpr static uint32_t indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
public:
    void onInit() override;

    void onDestroy() override;

    void onDraw() override;
};


#endif //PLAYOPENGL_SPLIT_RENDER_H
