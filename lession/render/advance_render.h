//
// Created by 王波 on 2022/6/12.
//

#ifndef PLAYOPENGL_ADVANCE_RENDER_H
#define PLAYOPENGL_ADVANCE_RENDER_H


#include "../../headers/IRender.h"

class AdvanceRender: IRender {
public:
    AdvanceRender(): IRender() {};
    ~AdvanceRender() = default;

private:
    void onInit() override;

    void onDraw() override;

    void onDestroy() override;

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    const char *vShaderPath = "resources/shaders/advance/vShader.vs";
    const char *fShaderPath = "resources/shaders/advance/fShader.fs";

    constexpr static float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
    };
};




#endif //PLAYOPENGL_ADVANCE_RENDER_H
