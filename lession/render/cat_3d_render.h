//
// Created by 王波 on 2022/6/25.
//

#ifndef PLAYOPENGL_CAT_3D_RENDER_H
#define PLAYOPENGL_CAT_3D_RENDER_H
#include "../../headers/IRender.h"
#include<list>
#include <cmath>
#include "../../headers/VertexUtils.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Cat3DRender:public IRender {
public:
    Cat3DRender(): IRender(){}
    ~Cat3DRender() = default;
    void onInit() override;

    void onDraw() override;

private:
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    uint32_t pointNums;
    uint32_t texture_body;
protected:
    const char *vShaderPath = "resources/shaders/cat/3d/vShader.vs";
    const char *fShaderPath = "resources/shaders/cat/3d/fShader.fs";

    constexpr static float vertices[] = {
    };

    constexpr static int indices[] =  {  // note that we start from 0!
    };

    void onDestroy() override {

    }

    void buildCatsBody(list<Vec8> *targetVertexes, list<Vec3> *targetIndicates);
};


#endif //PLAYOPENGL_CAT_3D_RENDER_H
