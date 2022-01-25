//
// Created by bo on 2022/1/25.
//
#include "headers/shader.h"

using namespace std;

Shader::Shader(const char *vertex_shader_path, const char *fragment_shader_path) {
    //1. read shader source codes
    string vertex_source;
    string fragment_source;

    ifstream vertex_file;
    ifstream fragment_file;

    //no need to check next exceptions
    vertex_file.exceptions(ifstream::failbit | ifstream::badbit);
    fragment_file.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        vertex_file.open(vertex_shader_path);
        fragment_file.open(fragment_shader_path);

        stringstream vertex_shader_stream, fragment_shader_stream;
        vertex_shader_stream << vertex_file.rdbuf();
        fragment_shader_stream << fragment_file.rdbuf();

        vertex_file.close();
        fragment_file.close();

        vertex_source = vertex_shader_stream.str();
        fragment_source = fragment_shader_stream.str();

        cout << "vertex source:" << vertex_source << endl;
    } catch (ifstream::failure e) {
        cerr << "load shader source file failed.\n" << "code:" << e.code() << " msg:" << e.what() << endl;
    }

    const char* vShaderCode = vertex_source.c_str();
    const char* fShaderCode = fragment_source.c_str();
    //2. load shader program
    //create shaders
    uint32_t vertex_shader = GLUtils::createShader(GL_VERTEX_SHADER, vShaderCode);
    uint32_t fragment_shader = GLUtils::createShader(GL_FRAGMENT_SHADER, fShaderCode);

    if (vertex_shader <0 || fragment_shader <0) {
        return;
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertex_shader);
    glAttachShader(programId, fragment_shader);
    glLinkProgram(programId);

    int sucess;
    char info[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(programId, 512, nullptr, info);
        cout << "create shader program failed.\n" << info << endl;
        programId = -1;
        return;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use() {
    if (programId != -1) {
        glUseProgram(programId);
    }
}

void Shader::setFloat(const std::string &valueName, float value) const {
    glUniform1f(glGetUniformLocation(programId, valueName.c_str()), value);
}

void Shader::setInt(const string &valueName, float value) const {
    glUniform1i(glGetUniformLocation(programId, valueName.c_str()), value);
}
