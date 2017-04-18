// useful libraries - https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
// using image libraries from this
// https://github.com/asamy/Snake
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include <iostream>
#include "SOIL2.h" 
#include "Shaders.hpp"


const GLchar* vertexShaderSource = 
{
  "#version 330 core \n"
  "\n"
  "layout (location = 0) in vec3 position; \n"
  "\n"
  "void main()\n"
  "{\n"
  "      gl_Position = vec4(position.x, position.y, position.z, 1.0); \n"
  "}\n"
};

const GLchar* fragmentShaderSource =
{
"#version 330 core\n"
"\n"
"out vec4 color;\n"
"\n"
"void main()\n"
"{\n"
"    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}" 
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main()
{
  //Game::Start();
  // initialize glfw
  if (!glfwInit())
  {
    std::cout << "failed to initialize\n";
    glfwTerminate();
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

  GLFWwindow* window = glfwCreateWindow(640, 480, "Pang", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  // initialize glew
  glewExperimental = GL_TRUE; 
  glewInit();

  // Define the viewport dimensions
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);  
  glViewport(0, 0, width, height);

  //shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  // create gl program
  // stuff from https://gist.github.com/hahuang65/0c7d14a6fedb221c8b87#file-main-cpp-L123
  //GLuint program = glCreateProgram();
  //GLuint fragmentShader = Shaders::Get_Fragment_Shader();
  //GLuint vertexShader = Shaders::Get_Vertex_Shader();
  //glAttachShader(program, vertexShader);
  //glAttachShader(program, fragmentShader);
  //glLinkProgram(program);

  //GLuint vao;
  //glGenVertexArrays(1, &vao);
  //glBindVertexArray(vao);

  //glUseProgram(program);

  GLfloat vertices[] = {
       0.5f,  0.5f, 0.0f,  // Top Right
       0.5f, -0.5f, 0.0f,  // Bottom Right
      -0.5f, -0.5f, 0.0f,  // Bottom Left
      -0.5f,  0.5f, 0.0f   // Top Left 
  };
  GLuint indices[] = {  // Note that we start from 0!
      0, 1, 3,   // First Triangle
      1, 2, 3    // Second Triangle
  };


  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO); 
  glGenBuffers(1, &VBO); 

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0); 

  glBindBuffer(GL_ARRAY_BUFFER, 0);  
  glBindVertexArray(0); 

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}
