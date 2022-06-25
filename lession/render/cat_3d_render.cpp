//
// Created by 王波 on 2022/6/25.
//

#include "cat_3d_render.h"
constexpr float Cat3DRender::vertices[];
constexpr int Cat3DRender::indices[];

void Cat3DRender::onInit() {
    shader = new Shader(vShaderPath, fShaderPath);

    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    //circle
    list<Vec8> *verticesList = new list<Vec8>();
    list<Vec3> *indicesList = new list<Vec3>();

    buildCatsBody(verticesList, indicesList);

    uint32_t indicatesSize = indicesList->size() * 3;
    uint32_t verticesSize = verticesList->size() * 8;

    float catVertices[verticesSize];
    VertexUtils::convertListToArray(verticesList, catVertices);

    int catIndicates[indicatesSize];
    VertexUtils::convertListToArray(indicesList, catIndicates);
    //开启z缓冲深度检测，防止画面被覆盖
    glEnable(GL_DEPTH_TEST);
    pointNums = indicatesSize;
    //bind VAO
    glBindVertexArray(VAO);

    //bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //draw triangle
    std::cout << sizeof (catVertices)/4 << endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof (catVertices), catVertices, GL_STATIC_DRAW);

    //bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (catIndicates), catIndicates, GL_STATIC_DRAW);

    //设置顶点属性指针
    int floatSize = sizeof (float );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 *floatSize, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * floatSize, (void*)(3 * floatSize));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * floatSize, (void*)(6 * floatSize));
    glEnableVertexAttribArray(2);

    //release
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader->use();
    texture_body = GLUtils::createTexture("resources/imgs/earth.png", GL_RGBA);
    shader->setInt("textureBody", 0);
}
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
int grad = 0;
void Cat3DRender::onDraw() {
    shader->use();
    //初始化单位矩阵
    glm::mat4 model = glm::mat4(1.0f);
    float value = glfwGetTime();
    grad = (grad -1)%(360);

    std::cout << value<< endl;

    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(grad+0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader->setMatrix("model", glm::value_ptr(model));

    glm::mat4 view = glm::mat4 (1.0f);
    //远离z轴
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    view       = glm::rotate(view, glm::radians(360.0f),glm::vec3(0.0f, 0.0f, 1.0f));
//    view       = glm::rotate(view, glm::radians(40.0f),glm::vec3(1.0f, 0.0f, 0.0f));
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

//    view = glm::lookAt(cameraPos,
//                       cameraPos + cameraFront,
//                       cameraUp);

    glm::mat4 projection = glm::mat4 (1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    shader->setMatrix("view", glm::value_ptr(view));
    shader->setMatrix("projection", glm::value_ptr(projection));

// draw rectangle
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_body);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(VAO);
//    glDrawElements(GL_LINE_LOOP, pointNums, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, pointNums, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

/**
 * 构建猫的身体顶点数组
 * @param targetVertexes
 * @param targetIndicates
 */
void Cat3DRender::buildCatsBody(list<Vec8> *targetVertexes, list<Vec3> *targetIndicates) {
    float xCenter = 0.0f;
    float yCenter = 0.0f;
    float zCenter = 0.0f;
//    VertexUtils::createCircleVertex(targetVertexes, targetIndicates, xCenter, yCenter, zCenter, 1.0f,32, 0.8f,0.8f,0.0f);
    VertexUtils::createBallVertex(targetVertexes, targetIndicates, xCenter, yCenter, zCenter, 2.0f,60,30, 0.8f,0.8f,0.0f);
}