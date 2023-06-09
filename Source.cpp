#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>


const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(1.0f,0.0f,0.0f, 1.0);\n"
"}\0";


int main()
{
    float liczbaUsera;
    std::cout << "Podaj liczbe: ";
    std::cin >> liczbaUsera;

    // inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Tworzenie okna
    const unsigned int window_width = 1000;
    const unsigned int window_height = 800;
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



    // vertex data
    //GLfloat **vertices = new GLfloat *[6];
    //GLfloat vertices[48];
    std::vector<GLfloat> vertices(liczbaUsera * 12*2);
    //GLfloat vertices [] 
    //    = {
    //    // coordinates          // colors
    //    -0.8f,  0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 1, 1
    //     0.8f, -0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 2, 3
    //    -0.8f, -0.6f, 0.0f,     0.0f, 1.0f, 0.0f // triangle 1   vertex 3
    //     
    //     
    //};

    float kat = 360 / liczbaUsera / 2;
    float r = 0.4f;
    for (int i = 0; i <= 2; i++) {
        for (int i = 0; i < liczbaUsera * 4; i++) {
            //std::cout << x;
            //std::cout << "kat to: " << kat << std::endl;
            float radiany = kat * 3.14159265359 / 180.0f;
            int x;
            if (i == 0) {
                x = 0;
            }
            else {
                x = i * 3;
            }
            vertices[x] = r * cos((360.0 / liczbaUsera * 3.14 / 180.0) * i);
            vertices[x + 1] = r * sin((360.0 / liczbaUsera * 3.14 / 180.0) * i);
            vertices[x + 2] = 0.0f;

            kat = kat + 360 / liczbaUsera / 2;

        }
    }
   


    //GLuint indices[] = {
    //    0, 1, 2   // triangle 2
    //};
    std::vector<GLuint> indices(liczbaUsera * 12);
    //GLuint indices[] = {
    //    0, 1, 2,    // triangle 1
    //    0, 2, 3,
    //    0, 3, 4,
    //    0, 4, 5,
    //    0, 5, 6,
    //    0, 6, 7,
    //    0, 7, 8,
    //    0, 8, 9
    //};

    for (int i = 0; i < liczbaUsera * 4; i++) {
        int x;
        x = i * 3;
        indices[x] = 0;
        indices[x + 1] = i;
        indices[x + 2] = i + 1;
    }
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(0);


    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

    // pętla zdarzeń
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 10000);
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
