//
// Created by 王波 on 2022/6/24.
//

#include "texture_drawer.h"
constexpr float TextureDrawer::vertices[];
constexpr int TextureDrawer::indices[];

void TextureDrawer::onInit() {
    shader = new Shader(vShaderPath, fShaderPath);

    VAO = GLUtils::createVAO();
    VBO = GLUtils::createBuffers();
    EBO = GLUtils::createBuffers();

    //circle
    list<Vec8> *verticesList = new list<Vec8>();
    list<Vec3> *indicesList = new list<Vec3>();

    provider->provideData(verticesList, indicesList);

    uint32_t indicatesSize = indicesList->size() * 3;
    uint32_t verticesSize = verticesList->size() * 8;

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
    texture_body = GLUtils::createTexture("resources/imgs/body.png", GL_RGBA);
    shader->setInt("textureBody", 0);
}

void TextureDrawer::onDraw() {
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

void TextureDrawer::setDataProvider(DataProvider *provider) {
    this->provider = provider;
}

void DataProvider::provideData(list<Vec8> *targetVertexes, list<Vec3> *targetIndicates) {

}
