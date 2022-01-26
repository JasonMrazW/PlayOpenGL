//
// Created by bo on 2022/1/25.
//

#ifndef PLAYOPENGL_TEXTURE_RENDER_H
#define PLAYOPENGL_TEXTURE_RENDER_H
#include "GLUtils.h"
#include "IRender.h"
#include "shader.h"
#include <std/std_image.h>

class TextureRender: public IRender {
public:
    TextureRender():IRender(){}
    ~TextureRender(){}

private:
    void onInit() override;

    void onDestroy() override;

    uint32_t createTexture(const char* imagePath, uint32_t rgbFormat);

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
    uint32_t textureA = -1;
    uint32_t textureB = -1;

    //texture coords: 指定texture的比例，1.0表示与图像大小一致，0.5某项仅50%
    //例如：全0.5，表示texture大小是原来的1/4大小
    constexpr static float verticesAndColors[] = {
            // positions          // colors           // texture coords
            0.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.0f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    constexpr static uint32_t indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    const static char *vShaderPath;
    const static char *fShaderPath;
protected:
    void onDraw() override;
};

#endif //PLAYOPENGL_TEXTURE_RENDER_H
