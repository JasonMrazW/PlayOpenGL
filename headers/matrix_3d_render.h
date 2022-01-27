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

    void onInput(GLFWwindow *window) override;

    void onCursorInput(GLFWwindow *window, double xPos, double yPos) override;

    void onScroll(GLFWwindow *window, double xPos, double yPos) override;

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    float cameraSpeed = 0.05f;
    float deltaTime = 0.0f;
    float lastTime =0.0f;

    float lastXPos, lastYPos;
    bool isFirstRender = true;

    float yaw = -90.0f, pitch = 0.0f;

    float fov = 45.0f;
};


#endif //PLAYOPENGL_MATRIX_3D_RENDER_H
