//
// Created by bo on 2022/1/26.
//

#ifndef PLAYOPENGL_MATRIX_RENDER_H
#define PLAYOPENGL_MATRIX_RENDER_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "texture_render.h"

class MatrixRender: TextureRender {
public:
    MatrixRender():TextureRender(){}
    ~MatrixRender() {}

private:
    void onDraw() override;
};

#endif //PLAYOPENGL_MATRIX_RENDER_H
