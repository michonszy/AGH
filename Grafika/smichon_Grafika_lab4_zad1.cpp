#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <iostream>
#include <sstream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
const float cameraSpeed = 0.03f;
float pitch = 0.0f;
float yaw = -90.0f;

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 2.5f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool first_window_enter = true;
GLfloat kolor1 = 0.0;
float previousX;
float previousY;
const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"layout(location = 2) in vec2 texture;\n"
"out vec3 vertexColor;\n"
"out vec2 vertexTexture;\n"
"uniform mat4 model;\n"
"uniform mat4 view; \n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"

"gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    vertexColor = color;\n"
"    vertexTexture = texture;\n"
"}\0";

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
    const unsigned int window_height = 800;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyboardCallback);

    glfwSetInputMode(window, GLFW_CURSOR, 1);
    glfwSetCursorPosCallback(window, mouseCallback);


    previousX = static_cast<float>(window_width) / 2.0f;
    previousY = static_cast<float>(window_height) / 2.0f;

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
    GLubyte* data = stbi_load("images/wood.jpeg", &width, &height, &nrChannels, 0);

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

    //// vertex data
    //GLfloat vertices[] = {
    //    // coordinates          // colors
    //    -0.8f,  0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 1, 1
    //     0.8f, -0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1,2 vertex 2, 3
    //    -0.8f, -0.6f, 0.0f,     0.0f, 1.0f, 0.0f, // triangle 1   vertex 3
    //     0.8f,  0.6f, 0.0f,     0.0f, 1.0f, 0.0f  // triangle 2   vertex 2
    //};

    //GLuint indices[] = {
    //    0, 1, 2,    // triangle 1
    //    0, 3, 1     // triangle 2
    //};

    GLfloat vertices[] = {
       -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

       -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

       -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

       -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

       -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
    };


    GLuint indices[] = {
        0,1,3,
        3,1,2,
        4,5,7,
        7,5,6,
        8,9,11,
        11,9,10,
        12,13,15,
        15,13,14,
        16,17,19,
        19,17,18,
        20,21,23,
        23,21,22
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);
    glEnable(GL_DEPTH_TEST);

    //do fps
    double previousTime = glfwGetTime();
    int frameCount = 0;
    double deltaTime;

    // pętla zdarzeń
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        //do fps
          // Measure speed
        double currentTime = glfwGetTime();
        frameCount++;

        deltaTime = currentTime - previousTime;
       const float cameraSpeed = 2.0f * deltaTime;

        // If a second has passed.
        if (currentTime - previousTime >= 1.0)
        {

            // Display the frame count here any way you want.
            std::cout << frameCount << std::endl;

            std::string s = std::to_string(frameCount);
            std::string s2 = std::to_string(currentTime);
            std::string s0 = "FPSy: ";
            std::string deltaTime = std::to_string(currentTime - previousTime);
            std::string calosc = "FPS:" + s + " deltaTime: " + deltaTime;
            char const* tytul = calosc.c_str();


            // std::cout << frameCount << std::endl;


            // const char* tytul2 = tytul;


            glfwSetWindowTitle(window, tytul);

            frameCount = 0;
            previousTime = currentTime;
        }

        //// transformations
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        ////model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        ////model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        //GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        sinTransform = sin(glfwGetTime());
        sinRotation = deltaTime * 5;
        sinSize = sin(glfwGetTime());

        // transformations przemieszczenie na boki i obrtotu
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(sinTransform, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-45.0f + sinRotation), glm::vec3(0.0f, 0.0f, 1.0f));
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::vec3 cameraFront_new;
        cameraFront_new.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront_new.y = sin(glm::radians(pitch));
        cameraFront_new.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(cameraFront_new);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);
        GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;



        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform1f(vertexColorLocation, kolor1);

        glDrawElements(GL_TRIANGLES, 1000, GL_UNSIGNED_INT, 0);
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


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (first_window_enter)
    {
        previousX = xpos;
        previousY = ypos;
        first_window_enter = false;
    }
    const float sensitivity = 0.05f;


    float xdifference = xpos - previousX;
    float ydifference = previousY - ypos;
    xdifference *= sensitivity;
    ydifference *= sensitivity;
    pitch += ydifference;
    yaw += xdifference;




    previousX = xpos;
    previousY = ypos;
}