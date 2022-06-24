//
// Created by 王波 on 2022/6/18.
//

#include "cat_render.h"
constexpr float CatRender::vertices[];
constexpr int CatRender::indices[];

void CatRender::onInit() {
    shader = new Shader(vShaderPath, fShaderPath);

    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    //circle
    list<Vec6> *verticesList = new list<Vec6>();
    list<Vec3> *indicesList = new list<Vec3>();

    buildCatsBody(verticesList, indicesList);

    uint32_t indicatesSize = indicesList->size() * 3;
    uint32_t verticesSize = verticesList->size() * 6;

    float catVertices[verticesSize];
    VertexUtils::convertListToArray(verticesList, catVertices);

    int catIndicates[indicatesSize];
    VertexUtils::convertListToArray(indicesList, catIndicates);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 *floatSize, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * floatSize, (void*)(3 * floatSize));
    glEnableVertexAttribArray(1);

    //release
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader->use();
    texture_body = GLUtils::createTexture("resources/imgs/body.png", GL_RGBA);
    shader->setInt("texture_body", 0);
}

void CatRender::onDraw() {

// draw triangle
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 12);
//    //release
//    glBindVertexArray(0);
    shader->use();
    //初始化单位矩阵
    glm::mat4 trans = glm::mat4(1.0f);

//    float value = glfwGetTime();
//    float x = (sin(value)/2.0f)+0.1f;
//    float y = (cos(value)/2.0f)+0.1f;
//    float grad = sin(value) * 10.f;
//
//
//    trans = glm::rotate(trans, glm::radians(grad), glm::vec3(0.0f, 0.0f, 1.0f));
//    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));

    shader->setMatrix("transform", glm::value_ptr(trans));

// draw rectangle
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_body);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, pointNums, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/**
 * 构建猫的身体顶点数组
 * @param targetVertexes
 * @param targetIndicates
 */
void CatRender::buildCatsBody(list<Vec6> *targetVertexes, list<Vec3> *targetIndicates) {
//圆心
    float xCenter = -0.32f;
    float yCenter = 0.28f;

    //left-ear
    VertexUtils::createTriangle(targetVertexes, targetIndicates, -0.55f, 0.4f,-0.5f, 0.5f, 0.5f,1.0f,1.0f);
    //right-ear
    VertexUtils::createTriangle(targetVertexes, targetIndicates, -0.2f, 0.4f, -0.15f, 0.5f,0.5f,1.0f,1.0f);
    //body
//    VertexUtils::createRectangle(targetVertexes, targetIndicates, 0.25f, 0.0f, 0.4f, 0.8f,0.8f,0.5f,0.2f);
    //head
    VertexUtils::createCircleVertex(targetVertexes, targetIndicates, xCenter, yCenter, 0.2f,32, 0.8f,0.8f,0.0f);
    //left-feet
    VertexUtils::createRectangle(targetVertexes, targetIndicates, 0.1f, -0.3f, 0.2f, 0.2f,0.2f,0.8f,0.5f);
    //right-feet
    VertexUtils::createRectangle(targetVertexes, targetIndicates, 0.5f, -0.3f, 0.2f, 0.2f,0.2f,0.8f,0.5f);

    //left-eyes
    VertexUtils::createStar(targetVertexes, targetIndicates, -0.4f, 0.35f, 0.03f,0.2f,0.5f,0.2f);
    //right-eyes
    VertexUtils::createStar(targetVertexes, targetIndicates, -0.25f, 0.35f, 0.03f,0.2f,0.5f,0.2f);
    //nose
    VertexUtils::createRectangle(targetVertexes, targetIndicates, -0.32f, 0.3f, 0.15f, 0.05f,0.1f,0.1f,0.05f);
    //mouse
    VertexUtils::createRectangle(targetVertexes, targetIndicates, -0.32f, 0.15f, 0.05f, 0.2f,0.8f,0.4f,0.8f);
}



