#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>

using namespace std;

const char *vertex_shader_source = "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                    "}\n\0";

const char *fragment_shader_source = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
                                     "}\n\0";

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
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

uint32_t createVAO() {
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
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

    //----------------------------------------
    //create VBO
    uint32_t vbo_buffer = createVBO();
    uint32_t vao_array = createVAO();

    glBindVertexArray(vao_array);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao_array);
    glDeleteBuffers(1, &vbo_buffer);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
