//
// Created by bo on 2022/1/24.
//

#ifndef PLAYOPENGL_GLUTILS_H
#define PLAYOPENGL_GLUTILS_H
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class GLUtils {
public:
static uint32_t createShader(uint32_t shader_type, const char *source) {
    uint32_t shader;
    shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];

    //check vertex shader is creat success
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "create shader failed.\n" << infoLog << std::endl;
        return -1;
    }
    return shader;
}

static uint32_t createBuffers() {
    uint32_t buffer;
    glGenBuffers(1, &buffer);
    return buffer;
}

static uint32_t createVAO() {
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    return VAO;
}
};
#endif //PLAYOPENGL_GLUTILS_H
