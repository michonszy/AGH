#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <iostream>


void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"layout(location = 2) in vec2 texture;\n"
"out vec3 vertexColor;\n"
"out vec2 vertexTexture;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"    vertexTexture = texture;\n"
"}\0";
GLfloat kolor1 = 0.5;
const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"in vec2 vertexTexture;\n"
"out vec4 fragmentColor;\n"
"uniform sampler2D uTexture;\n"
"uniform float ourColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = mix(texture(uTexture, vertexTexture), vec4(0.0, 1.0, 0.0, 0.0), ourColor);\n"
"}\0";

GLuint VBO;
GLuint EBO;
GLuint VAO;
GLfloat liczbaWierzcholkow = 6;
int main()
{
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

    // texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data = stbi_load("images/wall.jpg", &width, &height, &nrChannels, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // texture2
    int width2, height2, nrChannels2;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data2 = stbi_load("images/wood.jpeg", &width2, &height2, &nrChannels2, 0);

    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    // vertex data
    GLfloat vertices[] = {
        // coordinates          // colors           // texture coordinates
        -1.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // triangle 1,2 vertex 1, 1
         0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // triangle 1,2 vertex 2, 3
        -1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // triangle 1   vertex 3
         0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // triangle 2   vertex 2

         0.0f,0.0f,0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
         0.0f,-1.0f,0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         1.0f,0.0f,0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,    // triangle 1
        0, 3, 1 ,   // triangle 2
        4,5,6
    };


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);


    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

    // pętla zdarzeń
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        

        if (liczbaWierzcholkow == 3) {
           
            glBindTexture(GL_TEXTURE_2D, texture);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GL_FLOAT)));
            glBindVertexArray(0);
        }
        else if (liczbaWierzcholkow == 6) {
            glBindTexture(GL_TEXTURE_2D, texture2);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture2);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glBindTexture(GL_TEXTURE_2D, texture);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GL_FLOAT)));
            glBindVertexArray(0);
        }

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform1f(vertexColorLocation, kolor1);

       
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
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        liczbaWierzcholkow = 9;
        // vertex data
        GLfloat vertices[] = {
            // coordinates          // colors           // texture coordinates
            -1.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // triangle 1,2 vertex 1, 1
             0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // triangle 1,2 vertex 2, 3
            -1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // triangle 1   vertex 3
             0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // triangle 2   vertex 2

             0.0f,0.0f,0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
             0.0f,-1.0f,0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
             1.0f,0.0f,0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f
        };

        GLuint indices[] = {
            0, 1, 2,    // triangle 1
            0, 3, 1 ,   // triangle 2
            4,5,6
        };


       


        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);


        glBindVertexArray(0);


    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        liczbaWierzcholkow = 6;
        // vertex data
        GLfloat vertices[] = {
            // coordinates          // colors           // texture coordinates
            -1.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // triangle 1,2 vertex 1, 1
             0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // triangle 1,2 vertex 2, 3
            -1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // triangle 1   vertex 3
             0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f // triangle 2   vertex 2


        };

        GLuint indices[] = {
            0, 1, 2,    // triangle 1
            0, 3, 1
        };


     


        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);


        glBindVertexArray(0);


    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        liczbaWierzcholkow = 3;
        // vertex data
        GLfloat vertices[] = {

             0.0f,0.0f,0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
             0.0f,-1.0f,0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
             1.0f,0.0f,0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        };

        GLuint indices[] = {

            0,1,2
        };



        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);


        glBindVertexArray(0);


    }

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        kolor1 = kolor1 + 0.1;
    }
    else {
        kolor1 = kolor1 - 0.1;
    }

}