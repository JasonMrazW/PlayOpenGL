//
// Created by 王波 on 2022/6/11.
//

#include "glwindow.h"
#include "render/triangle_render.h"
#include "render/advance_render"
#include "render/advance_texture_render.h"
#include "render/advance_matrix_render.h"
#include "render/split_render.h"
#include "render/advance_framebuffer_render.h"
#include "render/cat_render.h"
#include "render/provider/cat_body_provider.h"

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
    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    //transparent background
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_FALSE);

    //create window
    GLFWwindow *window = glfwCreateWindow(800, 800, "Cat's Home", NULL, NULL);
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


    TextureDrawer *render =  new TextureDrawer();
    render->setDataProvider(new CatBodyProvider());
    render->onInit();
    renders->push_back(render);

    //4. receive input event
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        list<IRender*>::iterator it;
        for (it = renders->begin();it !=renders->end();it++) {
            (*it)->onDraw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    list<IRender*>::iterator it;
    for (it = renders->begin();it !=renders->end();it++) {
        (*it)->onDestroy();
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
