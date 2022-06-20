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
    list<Vec3> *verticesList = new list<Vec3>();
    list<Vec3> *indicesList = new list<Vec3>();

    buildCatsBody(verticesList, indicesList);

    uint32_t indicatesSize = indicesList->size() * 3;
    uint32_t verticesSize = verticesList->size() * 3;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float ), (void*)0);
    glEnableVertexAttribArray(0);

    //release
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader->use();
}

void CatRender::onDraw() {

// draw triangle
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 12);
//    //release
//    glBindVertexArray(0);

// draw rectangle
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, pointNums, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/**
 * 构建猫的身体顶点数组
 * @param targetVertexes
 * @param targetIndicates
 */
void CatRender::buildCatsBody(list<Vec3> *targetVertexes, list<Vec3> *targetIndicates) {
//圆心
    float xCenter = -0.32f;
    float yCenter = 0.28f;

    //left-ear
    VertexUtils::createTriangle(targetVertexes, targetIndicates, -0.55f, 0.4f,-0.5f, 0.5f);
    //right-ear
    VertexUtils::createTriangle(targetVertexes, targetIndicates, -0.2f, 0.4f, -0.15f, 0.5f);
    //head
    VertexUtils::createCircleVertex(targetVertexes, targetIndicates, xCenter, yCenter, 0.18f,30);
    //body
    VertexUtils::createRectangle(targetVertexes, targetIndicates, 0.4f, 0.0f, 0.4f, 0.8f);
}



