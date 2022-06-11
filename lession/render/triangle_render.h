//
// Created by 王波 on 2022/6/11.
//

#ifndef PLAYOPENGL_TRIANGLE_RENDER_H
#define PLAYOPENGL_TRIANGLE_RENDER_H


#include "../../headers/IRender.h"

class TriangleRender : IRender{
public:
    TriangleRender():IRender() {}
    ~TriangleRender() = default;

private:
    void onInit() override;

    void onDraw() override;

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    const char *vShaderPath = "resources/shaders/triangle/vShader.vs";
    const char *fShaderPath = "resources/shaders/triangle/fShader.fs";

    constexpr static float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
    };

    void onDestroy() override {

    }

    void onInput(GLFWwindow *window) override {
        IRender::onInput(window);
    }

    void onCursorInput(GLFWwindow *window, double xPos, double yPos) override {
        IRender::onCursorInput(window, xPos, yPos);
    }

    void onScroll(GLFWwindow *window, double xPos, double yPos) override {
        IRender::onScroll(window, xPos, yPos);
    }
};


#endif //PLAYOPENGL_TRIANGLE_RENDER_H