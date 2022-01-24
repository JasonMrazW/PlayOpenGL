//
// Created by bo on 2022/1/24.
//

#ifndef PLAYOPENGL_SHADERS_H
#define PLAYOPENGL_SHADERS_H
#include "GLUtils.h"
#include "IRender.h"

class Shaders:IRender {
public:
    Shaders():IRender() {}
    ~Shaders() {}

    void onInit() override;

    void onDraw() override;

    void onDestroy() override;
private:
    const char *vertex_shader_source = "#version 330 core\n"
                                "layout (location = 0) in vec3 pos;\n"
                                "out vec4 renderColor;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = vec4(pos, 1.0f);"
                                "   renderColor = vec4(0.5f, 0.5f, 1.0f, 1.0f);"
                                "}\n\0";

    const char *fragment_shader_source = "#version 330 core\n"
                                  "in vec4 renderColor;\n"
                                  "out vec4 FragColor;"
                                  "void main()\n"
                                  "{\n"
                                  " FragColor = renderColor;"
                                  "}\n\0";

    constexpr static float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f,
            0.5, 0.5f, 0.0f
    };

    uint32_t VBO;
    uint32_t VAO;
    uint32_t shaderProgram;
};

#endif //PLAYOPENGL_SHADERS_H
