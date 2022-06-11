//
// Created by 王波 on 2022/6/11.
//

#ifndef PLAYOPENGL_GLWINDOW_H
#define PLAYOPENGL_GLWINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../headers/IRender.h"

using namespace std;

class GLWindow {
public:
    GLWindow();
    ~GLWindow();

    void init();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    static void processInput(GLFWwindow* window);

private:
    IRender *render = nullptr;
};


#endif //PLAYOPENGL_GLWINDOW_H
