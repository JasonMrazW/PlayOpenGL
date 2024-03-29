//
// Created by bo on 2022/1/25.
//

#include "../headers/texture_render.h"
#include <iostream>
#include <cmath>

const char *TextureRender::vShaderPath = "resources/shaders/textures/vShader.vs";
const char *TextureRender::fShaderPath = "resources/shaders/textures/fShader.fs";
constexpr float TextureRender::verticesAndColors[];
constexpr uint32_t TextureRender::indices[];

using namespace std;

void TextureRender::onInit() {
    shader = new Shader(vShaderPath, fShaderPath);

    //create VBO、VAO
    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAndColors), verticesAndColors, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float ), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float ), (void *)(3 * sizeof (float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void *)(6 * sizeof (float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //create texture
    textureA = createTexture("resources/imgs/container.jpg", GL_RGB);
    textureB = createTexture("resources/imgs/awesomeface.png", GL_RGBA);
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
}

void TextureRender::onDraw() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureA);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureB);

    float time = glfwGetTime();
    float greenValue = (sin(time)/2.0f) + 0.5f; //-0.5~0.5===>0~1
    shader->setFloat("mixValue", greenValue);

    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureRender::onDestroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

uint32_t TextureRender::createTexture(const char *imagePath, uint32_t rgbFormat) {
    uint32_t textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    uint8_t *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, rgbFormat, width, height, 0, rgbFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "load local image failed." << endl;
    }
    stbi_image_free(data);

    return textureId;
}
