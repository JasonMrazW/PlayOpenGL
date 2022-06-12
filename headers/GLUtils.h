//
// Created by bo on 2022/1/24.
//

#ifndef PLAYOPENGL_GLUTILS_H
#define PLAYOPENGL_GLUTILS_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <std/std_image.h>

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

    static uint8_t * loadImage(const char *imagePath, int *width, int *height, int *nrChannels) {
        stbi_set_flip_vertically_on_load(true);

        uint8_t *data = stbi_load(imagePath, reinterpret_cast<int *>(width), reinterpret_cast<int *>(height),
                                  reinterpret_cast<int *>(nrChannels), 0);
        return data;
    }

    static uint32_t createTexture(const char *imagePath, int rgbFormat) {
        uint32_t textureId;

        //init texture
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        uint8_t *imageData = loadImage(imagePath, &width, &height, &nrChannels);
        if (imageData) {
            cout << "load local image succeed." << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, rgbFormat, width, height, 0, rgbFormat, GL_UNSIGNED_BYTE, imageData);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            cout << "load local image failed." << endl;
        }
        stbi_image_free(imageData);
        return textureId;
    }
};
#endif //PLAYOPENGL_GLUTILS_H