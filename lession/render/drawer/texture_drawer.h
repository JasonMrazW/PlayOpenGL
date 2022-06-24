//
// Created by 王波 on 2022/6/24.
//

#ifndef PLAYOPENGL_TEXTURE_DRAWER_H
#define PLAYOPENGL_TEXTURE_DRAWER_H
#include "../../../headers/IRender.h"
#include<list>
#include <cmath>
#include "../../../headers/VertexUtils.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class DataProvider {
public:
    virtual void provideData(list<Vec8> *targetVertexes, list<Vec3> *targetIndicates);
};

class TextureDrawer: public IRender{
public:
    TextureDrawer(): IRender(){}
    ~TextureDrawer() = default;
    void setDataProvider(DataProvider *provider);
    void onInit() override;

    void onDraw() override;

private:
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    uint32_t pointNums;
    uint32_t texture_body;
    DataProvider *provider;
protected:
    const char *vShaderPath = "resources/shaders/cat/texture/vShader.vs";
    const char *fShaderPath = "resources/shaders/cat/texture/fShader.fs";

    constexpr static float vertices[] = {
    };

    constexpr static int indices[] =  {  // note that we start from 0!
    };

    void onDestroy() override {

    }
};




#endif //PLAYOPENGL_TEXTURE_DRAWER_H
