#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
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

float previousX;
float previousY;
const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"uniform mat4 model;\n"
"uniform mat4 view; \n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"

"gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    vertexColor = color;\n"
"}\0";

//const GLchar* fragmentShaderSource =
//"#version 330 core\n"
//"in vec3 vertexColor;\n"
//"out vec4 fragmentColor;\n"
//"void main()\n"
//"{\n"
//"    fragmentColor = vec4(vertexColor, 1.0);\n"
//"}\0";


const GLchar* fragmentShaderSource =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"vec3 objectColor = vec3(0.0, 1.0, 0.0);\n"
"vec3 lightColor = vec3(1.0, 1.0, 1.0); \n"
"vertexNormal = mat3(transpose(inverse(model))) * normal;\n"
"vec3 normalNormalized = normalize(vertexNormal);\n"
"vec3 lightDirection = normalize(lightPosition - fragmentPosition);\n"
"float diffuse = max(dot(normalNormalized, lightDirection), 0.0);\n"
"vec3 diffuseColor = diffuse * lightColor;\n"
"void main()\n"
"{\n"
"   fragmentPosition = vec3(model * vec4(position, 1.0));;\n"
"}\0";

const GLchar* fragmentSunSource =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"uniform vec3 lightPosition; \n"
"out vec3 fragmentPosition;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"    fragmentPosition = vec3(model * vec4(position, 1.0));\n"
"vertexNormal = mat3(transpose(inverse(model))) * normal;\n"
"}\0";

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



    //slonce
    GLuint fragmentSunShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentSunShader, 1, &fragmentSunSource, NULL);
    glCompileShader(fragmentSunShader);

    glGetShaderiv(fragmentSunShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentSunShader, 512, NULL, error_message);
        std::cout << "Error (fragmentSunShader shader): " << error_message << std::endl;
    }


    GLuint SunshaderProgram = glCreateProgram();
    glAttachShader(SunshaderProgram, vertexShader);
    glAttachShader(SunshaderProgram, fragmentSunShader);
    glLinkProgram(SunshaderProgram);

    glGetProgramiv(SunshaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(SunshaderProgram, 512, NULL, error_message);
        std::cout << "Error (Shader program): " << error_message << std::endl;
    }

    glDetachShader(SunshaderProgram, vertexShader);
    glDetachShader(SunshaderProgram, fragmentSunShader);


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
    glDeleteShader(fragmentSunShader);

    GLfloat vertices[] = {
        // vertices coords      // normals 
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f
    };

    GLuint indices[] = {
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        12,13,14,
        15,16,17,
        18,19,20,
        21,22,23,
        24,25,26,
        27,28,29,
        30,31,32,
        33,34,35
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


    glBindVertexArray(0);


    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);
    glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    // pętla zdarzeń
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // transformations
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        
        //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.5f, 0.0f));
        model = glm::translate(model, glm::vec3(1.0f, 0.7f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));




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

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 1000, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::rotate(model2, glm::radians(-45.0f), glm::vec3(1.0f, 0.5f, 0.0f));
        model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
        GLint modelLoc2 = glGetUniformLocation(SunshaderProgram, "model");
        glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));

        glm::mat4 view2 = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        GLint viewLoc2 = glGetUniformLocation(SunshaderProgram, "view");
        glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view2));

        glm::mat4 projection2 = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);
        GLint projectionLoc2 = glGetUniformLocation(SunshaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(projection2));

        glUseProgram(SunshaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 1000, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
       

        glUniform3f(glGetUniformLocation(fragmentSunShader, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
      
        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(SunshaderProgram);

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
