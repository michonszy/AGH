#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

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


float sinTransform = 0;
float sinRotation = 0;
float sinSize = 0;

int main()
{
    // inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Tworzenie okna
    const unsigned int window_width = 1000;
    const unsigned int window_height = 1000;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


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


    //// vertex data
    //GLfloat vertices[] = {
    //    // coordinates          // colors
    //    -0.8f,  0.6f, 0.0f,     1.0f, 1.0f, 0.0f, // triangle 1,2 vertex 1, 1
    //     0.8f, -0.6f, 0.0f,     1.0f, 1.0f, 1.0f, // triangle 1,2 vertex 2, 3
    //    -0.8f, -0.6f, 0.0f,     1.0f, 1.0f, 0.0f, // triangle 1   vertex 3
    //     0.8f,  0.6f, 0.0f,     0.0f, 0.0f, 0.0f, // triangle 2   vertex 2

    //     0.4f,  -0.3f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 1, 1
    //     -0.4f, 0.3f, 0.0f,     1.0f, 1.0f, 1.0f, // triangle 1,2 vertex 2, 3
    //    0.4f, 0.3f, 0.0f,     1.0f, 0.0f, 0.0f, // triangle 1   vertex 3
    //     -0.4f,  -0.3f, 0.0f,     0.0f, 1.0f, 0.0f  // triangle 2   vertex 2
    //};
        // vertex data
    GLfloat vertices[] = {
        // coordinates          // colors
        -1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 0.0f, // triangle 1,2 vertex 1, 1
         -0.8f, 0.3f, 0.0f,     1.0f, 1.0f, 0.0f, // triangle 1,2 vertex 2, 3
        0.0f,0.0f, 0.0f,        1.0f, 1.0f, 0.0f, // triangle 1   vertex 3

        //pierwszy zolty ruch na boki
         
        -0.7f,  0.3f, 0.0f,     1.0f, 0.0f, 0.0f, // triangle 1,2 vertex 1, 1
         0.7f, -0.3f, 0.0f,     1.0f, 0.0f, 0.0f, // triangle 1,2 vertex 2, 3   
        0.7f,  0.3f, 0.0f,      1.0f, 0.0f, 0.0f, // triangle 2   vertex 2

        //drugi czerwony obrot

          0.4f,  -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 1, 1
         -0.4f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 2, 3
          0.4f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1   vertex 3


          //trzeci zielony powiekszanie

          1.0f,  -0.3f, 0.0f,     0.0f, 0.0f, 1.0f, // triangle 1,2 vertex 1, 1
         -1.0f, 0.3f, 0.0f,     0.0f, 0.0f, 1.0f, // triangle 1,2 vertex 2, 3
         -1.0f,  -0.3f, 0.0f,     0.0f, 0.0f, 1.0f  // triangle 2   vertex 2

         //czwarty niebieski wszystko
    };
    GLuint indices[] = {
        0, 1, 2,    // triangle 1
        3,4,5,
        6,7,8,
        9,10,11
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

        sinTransform = sin(glfwGetTime()*2);
        sinRotation = sin(glfwGetTime()*200);
        sinSize = sin(glfwGetTime()*2);

        // transformations przemieszczenie na boki
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(sinTransform, -0.5f, 0.0f));
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // transformations rotacja
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::rotate(model2, glm::radians(-45.0f + sinRotation), glm::vec3(0.0f, 0.0f, 1.0f));
        GLint modelLoc2 = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GL_FLOAT)));
        glBindVertexArray(0);

        //transformacja powiekszanie
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::scale(model3, glm::vec3(sinSize, sinSize, sinSize));
        GLint modelLoc3 = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc3, 1, GL_FALSE, glm::value_ptr(model3));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GL_FLOAT)));
        glBindVertexArray(0);


        //transformacja wszystko
        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::translate(model4, glm::vec3(sinTransform, -0.5f, 0.0f));
        model4 = glm::rotate(model4, glm::radians(-45.0f + sinRotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model4 = glm::scale(model4, glm::vec3(sinSize, sinSize, sinSize));

        GLint modelLoc4 = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc4, 1, GL_FALSE, glm::value_ptr(model4));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(9 * sizeof(GL_FLOAT)));
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