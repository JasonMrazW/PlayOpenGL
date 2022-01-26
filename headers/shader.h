//
// Created by bo on 2022/1/25.
//

#ifndef PLAYOPENGL_SHADER_H
#define PLAYOPENGL_SHADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "GLUtils.h"

class Shader {
public:
    uint32_t programId;

    Shader(const char* vertex_shader_path, const char* fragment_shader_path);

    void use();

    void setFloat(const std::string &valueName, float value) const;

    void setInt(const std::string &valueName, float value) const;

    void setMatrix(const std::string &valueName, const float *matrix) const;
};
#endif //PLAYOPENGL_SHADER_H
