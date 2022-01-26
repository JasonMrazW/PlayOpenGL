#include <iostream>
#include "headers/triangle.h"
#include "headers/shader_render.h"
#include "headers/texture_render.h"
#include "headers/matrix_render.h"
#include "headers/matrix_3d_render.h"
#define STB_IMAGE_IMPLEMENTATION
#include <std/std_image.h>
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0,width,height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }
}

int main() {
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(540, 540, "glWindow", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "glad init failed." << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    IRender *render = reinterpret_cast<IRender *>(new Matrix3DRender());
    render->onInit();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    int attr_number;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attr_number);
    std::cout << "max attr nums:" << attr_number << endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render->onDraw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    render->onDestroy();

    glfwTerminate();
    return 0;
}
