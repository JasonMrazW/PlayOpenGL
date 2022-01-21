#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>

using namespace std;

const char *vertex_shader_source = "#version 330 core\n"
                                    "layout (location = 12) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                    "}\0";

const char *fragment_shader_source = "#version 330 core\n"
                                     "out vec4 fragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  fragColor = vec4(1.0f, 1.0f, 0.5f, 1.0f);"
                                     "}\0";

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0,width/2,height/2);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }
}

uint32_t createShader(uint32_t shader_type, const char *source) {
    uint32_t shader;
    shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];

    //check vertex shader is creat success
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "create vertex shader failed.\n" << infoLog << endl;
        return -1;
    }
    return shader;
}

uint32_t createVBO() {
    uint32_t VBO;
    glGenBuffers(1, &VBO);
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
    window = glfwCreateWindow(540, 960, "glWindow", NULL, NULL);
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

    //create shader
    uint32_t vertexShader = createShader(GL_VERTEX_SHADER, vertex_shader_source);
    uint32_t fragmentShader = createShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    if (vertexShader < 0 || fragmentShader < 0) {
        return -1;
    }

    //create programmer
    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int sucess;
    char info[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        cout << "create shader program failed.\n" << info << endl;
        return -1;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //create VBO
    uint32_t vbo_buffer = createVBO();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        /* Render here */


        glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribIPointer(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
        glEnableVertexAttribArray(0);

        glUseProgram(shaderProgram);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
