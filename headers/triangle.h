//
// Created by bo on 2022/1/24.
//

#ifndef PLAYOPENGL_TRIANGLE_H
#define PLAYOPENGL_TRIANGLE_H
#include "GLUtils.h"
#include "IRender.h"
#include <iostream>

class Triangle:  IRender{
public:
    Triangle():IRender() {}
    ~Triangle() {}

    void onInit() override;

    void onDraw() override;

    void onDestroy() override;

private:
    const char *vertex_shader_source = "#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                       "}\n\0";

    const char *fragment_shader_source = "#version 330 core\n"
                                         "out vec4 fragColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "  fragColor = vec4(1.0f, 0.5f, 0.9f, 1.0f);"
                                         "}\n\0";

    uint32_t VAO;
    uint32_t VBO;
    uint32_t shaderProgram;

    constexpr static float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, 0.5f,0.0f,
            };

    //
    constexpr static unsigned int indicators[] = {
        0, 2, 3,   // first triangle
        1, 2, 3    // second triangle
    };
};
#endif //PLAYOPENGL_TRIANGLE_H
