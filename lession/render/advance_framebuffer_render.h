//
// Created by 王波 on 2022/6/13.
//

#ifndef PLAYOPENGL_ADVANCE_FRAMEBUFFER_RENDER_H
#define PLAYOPENGL_ADVANCE_FRAMEBUFFER_RENDER_H


#include "../../headers/IRender.h"
#include "advance_texture_render.h"

class AdvanceFrameBufferRender: public AdvanceTextureRender {
public:
    AdvanceFrameBufferRender(int width, int height):AdvanceTextureRender() {
        this->width = width;
        this->height = height;
    }
    ~AdvanceFrameBufferRender() = default;

    void onDraw() override;
    void initShader() override;
    void onInit() override;

    const char *vShaderPath = "resources/shaders/advance/framebuffer/vShader.vs";
    const char *fShaderPath = "resources/shaders/advance/framebuffer/fShader.fs";

private:
    Shader *screenShader = nullptr;
    uint32_t FBO;
    uint32_t texture1;
    int width, height;
    uint32_t QUAD_VAO;
    uint32_t QUAD_VBO;
    constexpr static float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f,0.0f, 1.0f,
                -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,
                1.0f, -1.0f,  0.0f,1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f,0.0f, 1.0f,
                1.0f, -1.0f,  0.0f,1.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f
    };
};


#endif //PLAYOPENGL_ADVANCE_FRAMEBUFFER_RENDER_H
