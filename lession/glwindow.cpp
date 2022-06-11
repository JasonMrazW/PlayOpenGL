//
// Created by 王波 on 2022/6/11.
//

#include "glwindow.h"
#include "render/triangle_render.h"

GLWindow::GLWindow() {

}

GLWindow::~GLWindow() {

}

void GLWindow::init() {
    //1. init glfw window
    if (!glfwInit())
        return;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //for mac os
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //no border
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    //transparent background
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_FALSE);

    //create window
    GLFWwindow *window = glfwCreateWindow(800, 800, "opengl window", NULL, NULL);
    if (!window) {
        std::cout << "failed to create window" << endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    //2. init glad
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        cout << "failed to init glad" << endl;
        return;
    }

    //3. init viewport
    //glViewport(0,0,400,400);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    render =  reinterpret_cast<IRender *>(new TriangleRender());
    render->onInit();
    //4. receive input event
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        render->onDraw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

//window size changed listener
void GLWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0,width,height);
}

void GLWindow::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
