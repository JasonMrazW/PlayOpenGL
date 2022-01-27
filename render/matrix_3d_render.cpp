//
// Created by bo on 2022/1/26.
//

#include "../headers/matrix_3d_render.h"
const static glm::vec3 positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};
void Matrix3DRender::onInit() {
    vShaderPath = "resources/shaders/3d/vShader.vs";
    fShaderPath = "resources/shaders/3d/fShader.fs";

    shader = new Shader(vShaderPath, fShaderPath);

    //开启z缓冲深度检测，防止画面被覆盖
    glEnable(GL_DEPTH_TEST);

    //create VBO、VAO
    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();

    glBindVertexArray(VAO);

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float ), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float ), (void *)(3 * sizeof (float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //create texture
    textureA = createTexture("resources/imgs/container.jpg", GL_RGB);
    textureB = createTexture("resources/imgs/awesomeface.png", GL_RGBA);
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
}



void Matrix3DRender::onDraw() {
    glm::mat4 view = glm::mat4 (1.0f);
    //远离z轴
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    view = glm::lookAt(cameraPos,
                       cameraPos + cameraFront,
                       cameraUp);

    glm::mat4 projection = glm::mat4 (1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    shader->setMatrix("view", glm::value_ptr(view));
    shader->setMatrix("projection", glm::value_ptr(projection));
    glm::vec3 a;
    glm::vec3 b;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureA);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureB);

    float time = glfwGetTime();
    float greenValue = (sin(time)/2.0f) + 0.5f; //-0.5~0.5===>0~1
    shader->setFloat("mixValue", greenValue);
    shader->use();

    glBindVertexArray(VAO);
    for (int i = 0; i < 10; ++i) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, positions[i]);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
        shader->setMatrix("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Matrix3DRender::onInput(GLFWwindow *window) {
    //拉进摄像机和中心点的距离
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }

    //远离设计相机和中心点的距离
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }

    //左移，远离X轴
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //求出X轴的向量
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    //右移，拉进和X轴的距离
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //求出X轴的向量
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}
