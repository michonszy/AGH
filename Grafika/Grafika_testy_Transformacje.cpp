#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"uniform mat4 model;\n"
"void main()\n"
"{\n"
"    gl_Position = model * vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(vertexColor, 1.0);\n"
"}\0";

float obrot = -30.0f;

float przyblizenie1 = 0.5f;
float przyblizenie2 = 0.5f;
float przyblizenie3 = 0.5f;
int main()
{
    // inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Tworzenie okna
    const unsigned int window_width = 700;
    const unsigned int window_height = 700;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //dodanie callbackow do klawiatury i myszy
    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetScrollCallback(window, scroll_callback);
    // inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // shadery
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    GLchar error_message[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, error_message);
        std::cout << "Error (Vertex shader): " << error_message << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, error_message);
        std::cout << "Error (Fragment shader): " << error_message << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, error_message);
        std::cout << "Error (Shader program): " << error_message << std::endl;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // vertex data
    GLfloat vertices[] = {
        // coordinates          // colors
        -0.8f,  0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 1, 1
         0.8f, -0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 2, 3
        -0.8f, -0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1   vertex 3
         0.8f,  0.6f, 0.0f,     0.0f, 1.0f, 0.0f  // triangle 2   vertex 2
    };

    GLuint indices[] = {
        0, 1, 2,    // triangle 1
        0, 3, 1     // triangle 2
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

    // pętla zdarzeń
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // transformations
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(obrot), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(przyblizenie1,przyblizenie2,przyblizenie3));
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        obrot--;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        obrot++;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        przyblizenie1 = przyblizenie1 + 0.1f;
        przyblizenie2 = przyblizenie2 + 0.1f;
        przyblizenie3 = przyblizenie3 + 0.1f;
    }
    else {
        przyblizenie1 = przyblizenie1-0.1f;
        przyblizenie2 = przyblizenie2-0.1f;
        przyblizenie3 = przyblizenie3-0.1f;
    }

}
