//
// Created by bo on 2022/1/26.
//

#ifndef PLAYOPENGL_MATRIX_3D_RENDER_H
#define PLAYOPENGL_MATRIX_3D_RENDER_H
#include "texture_render.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Matrix3DRender: TextureRender {
public:
    Matrix3DRender():TextureRender(){}
    ~Matrix3DRender() {}

private:
    void onInit() override;

    void onDraw() override;

    glm::vec3 *cubePositions = nullptr;
};


#endif //PLAYOPENGL_MATRIX_3D_RENDER_H
