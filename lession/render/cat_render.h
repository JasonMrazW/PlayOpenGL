//
// Created by 王波 on 2022/6/18.
//

#ifndef PLAYOPENGL_CAT_RENDER_H
#define PLAYOPENGL_CAT_RENDER_H
#include "../../headers/IRender.h"
#include<list>
#include <cmath>
#include "../../headers/VertexUtils.h"


class CatRender: IRender {
public:
    CatRender():IRender() {}
    ~CatRender() = default;

private:
    void onInit() override;

    void onDraw() override;

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    uint32_t pointNums;
    uint32_t texture_body;

    const char *vShaderPath = "resources/shaders/cat/vShader.vs";
    const char *fShaderPath = "resources/shaders/cat/fShader.fs";

    constexpr static float vertices[] = {
            //左耳
            -0.5f, 0.5f, 0.0f, // up
            -0.55f, 0.4f, 0.0f, // left
            -0.45f,  0.4f, 0.0f, // right
////
//            //右耳
//            -0.15f, 0.5f, 0.0f, // up
//            -0.2f, 0.4f, 0.0f, // left
//            -0.1f,  0.4f, 0.0f, // right
////
//            //身体
//            0.0f, 0.25f, 0.0f, // left-top
//            0.0f, -0.2f, 0.0f, // left-bottom
//            0.75f,  -0.2f, 0.0f, //right-bottom
//            0.75f, 0.25f, 0.0f, // right-top

    };

    constexpr static int indices[] =  {  // note that we start from 0!
            0, 1, 2,   // 左耳
//            3, 4, 5,    // 右耳
//            6, 7, 8,   // 左边三角形
//            6, 9, 8,   // 右边三角形
    };

    void onDestroy() override {

    }

    void buildCatsBody(list<Vec6> *targetVertexes, list<Vec3> *targetIndicates);
};


#endif //PLAYOPENGL_CAT_RENDER_H
