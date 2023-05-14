#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLfloat kolor1 = 1.0f;
GLfloat kolor2 = 0.0f;
GLfloat kolor3 = 0.0f;

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

//const GLchar* fragmentShaderSource =
//"#version 330 core\n"
//"in vec3 vertexColor;\n"
//"out vec4 fragmentColor;\n"
//"void main()\n"
//"{\n"
//"    fragmentColor = vec4(1.0f,0.0f,0.0f, 1.0);\n"
//
//"}\0";


const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";
float liczbaUsera = 8;
GLuint VBO;
GLuint EBO;





int main()
{


    
    //std::cout << "Podaj liczbe: ";
    //std::cin >> liczbaUsera;
    //if (!std::cin) {
    //    // input was not an integer ask again
    //    std::cout << "NIE PODAŁEŚ ODPOWIEDNIEGO ARGUMENTU NA WEJŚCIU, KOŁO SIĘ NIE NARYSUJE!" << std::endl;
    //}

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

    std::vector<GLfloat> vertices(liczbaUsera * 12);
    std::vector<GLuint> indices(liczbaUsera * 12);
    float kat = 360 / liczbaUsera / 2;
    float r = 0.4f;

    for (int i = 0; i < liczbaUsera; i++) {
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


    //GLuint indices[] = {
    //    0, 1, 2   // triangle 2
    //};

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

    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
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
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, kolor1, kolor2, kolor3, 1.0f);


        glDrawElements(GL_TRIANGLES, liczbaUsera*3, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 10000);
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
        kolor1 = 1.0f;
        kolor2 = 0.0f;
        kolor3 = 0.0f;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        kolor1 = 0.0f;
        kolor2 = 1.0f;
        kolor3 = 0.0f;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        kolor1 = 0.0f;
        kolor2 = 0.0f;
        kolor3 = 1.0f;
    }

}
double poprzedniStanY = 0.0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        liczbaUsera++;

       // glDrawElements(GL_TRIANGLES, liczbaUsera * 3, GL_UNSIGNED_INT, 0);
       glfwSetWindowShouldClose(window, true);
       main();
    }
    else {
        liczbaUsera--;
        
        //glDrawElements(GL_TRIANGLES, liczbaUsera * 3, GL_UNSIGNED_INT, 0);
        glfwSetWindowShouldClose(window, true);
        main();
    }
    yoffset = poprzedniStanY;
}