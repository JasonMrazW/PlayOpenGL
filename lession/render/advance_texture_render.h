//
// Created by 王波 on 2022/6/12.
//

#ifndef PLAYOPENGL_ADVANCE_TEXTURE_RENDER_H
#define PLAYOPENGL_ADVANCE_TEXTURE_RENDER_H
#include "../../headers/GLUtils.h"

#include "../../headers/IRender.h"

class AdvanceTextureRender: public IRender {
public:
    AdvanceTextureRender():IRender() {}
    ~AdvanceTextureRender() = default;

private:

    void onDestroy() override;

    uint32_t VBO;
    uint32_t EBO;

    uint32_t texture1;
    uint32_t texture2;

    const char *vShaderPath = "resources/shaders/advance/texture/vShader.vs";
    const char *fShaderPath = "resources/shaders/advance/texture/fShader.fs";

    constexpr static float verticesAndColors[] = {
            // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

    constexpr static float rectangle_vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };

    constexpr static uint32_t indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

protected:
    virtual void initShader();

    void onDraw() override;

    void onInit() override;

    uint32_t VAO;
};


#endif //PLAYOPENGL_ADVANCE_TEXTURE_RENDER_H
