//
// Created by bo on 2022/1/25.
//

#ifndef PLAYOPENGL_TEXTURE_RENDER_H
#define PLAYOPENGL_TEXTURE_RENDER_H
#include "GLUtils.h"
#include "IRender.h"
#include "shader.h"
#include <std/std_image.h>

class TextureRender: IRender {
public:
    TextureRender():IRender(){}
    ~TextureRender(){}

private:
    void onInit() override;

    void onDraw() override;

    void onDestroy() override;

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
    uint32_t textureId = -1;

    constexpr static float verticesAndColors[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    constexpr static uint32_t indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    const static char *vShaderPath;
    const static char *fShaderPath;
};

#endif //PLAYOPENGL_TEXTURE_RENDER_H
