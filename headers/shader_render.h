//
// Created by bo on 2022/1/24.
//

#ifndef PLAYOPENGL_ADVANCE_RENDER_H
#define PLAYOPENGL_SHADER_RENDER_H
#include "GLUtils.h"
#include "IRender.h"

class ShaderRender: IRender {
public:
    ShaderRender(): IRender() {}
    ~ShaderRender() {}

    void onInit() override;

    void onDraw() override;

    void onDestroy() override;
private:

    constexpr static float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f,
            0.5, 0.5f, 0.0f
    };

    constexpr static float verticesAndColors[] = {
            // positions         // colors
            -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };

    uint32_t VBO;
    uint32_t VAO;
};

#endif //PLAYOPENGL_ADVANCE_RENDER_H
//const char *vertex_shader_source = "#version 330 core\n"
//                                   "layout (location = 0) in vec3 pos;\n"
//                                   //"out vec4 renderColor;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "   gl_Position = vec4(pos, 1.0f);"
//                                   //"   renderColor = vec4(0.5f, 0.5f, 1.0f, 1.0f);"
//                                   "}\n\0";
//const char *fragment_shader_source = "#version 330 core\n"
//                                     "uniform vec4 renderColor;\n"
//                                     "out vec4 FragColor;"
//                                     "void main()\n"
//                                     "{\n"
//                                     "  FragColor = renderColor;"
//                                     "}\n\0";
//
//const char *vertex_shader_source_2 = "#version 330 core\n"
//                                     "layout (location = 0) in vec3 vertexPos;\n"
//                                     "layout (location = 1) in vec3 colorPos;"
//                                     "out vec4 renderColor;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "   gl_Position = vec4(vertexPos, 1.0f);"
//                                     "   renderColor = vec4(colorPos, 1.0f);"
//                                     "}\n\0";
//
//const char *fragment_shader_source_2 = "#version 330 core\n"
//                                       "in vec4 renderColor;\n"
//                                       "out vec4 FragColor;"
//                                       "void main()\n"
//                                       "{\n"
//                                       "  FragColor = renderColor;"
//                                       "}\n\0";