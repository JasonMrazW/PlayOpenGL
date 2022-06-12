//
// Created by 王波 on 2022/6/12.
//

#ifndef PLAYOPENGL_ADVANCE_MATRIX_RENDER_H
#define PLAYOPENGL_ADVANCE_MATRIX_RENDER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "advance_texture_render.h"

class AdvanceMatrixRender : AdvanceTextureRender {
public:
    AdvanceMatrixRender(): AdvanceTextureRender() {}
    ~AdvanceMatrixRender() = default;

protected:
    void onDraw() override;

    void initShader() override;

    const char *vShaderPath = "resources/shaders/advance/matrix/vShader.vs";
    const char *fShaderPath = "resources/shaders/advance/matrix/fShader.fs";
};


#endif //PLAYOPENGL_ADVANCE_MATRIX_RENDER_H
