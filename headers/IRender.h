//
// Created by bo on 2022/1/24.
//

#ifndef PLAYOPENGL_IRENDER_H
#define PLAYOPENGL_IRENDER_H
#include "shader.h"

class IRender {
public:
    IRender() {}
    ~IRender() {}
    virtual void onInit() = 0;
    virtual void onDraw() = 0;
    virtual void onDestroy() = 0;

    virtual void onInput(GLFWwindow *pWwindow) {

    }

protected:
    Shader *shader = nullptr;
};
#endif //PLAYOPENGL_IRENDER_H
