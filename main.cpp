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
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec2 texCoord;\n"
"\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 1.0f);\n"
"    ourColor = color;\n"
"    TexCoord = texCoord;\n"
"}\n"
};

const GLchar* fragmentShaderSource =
{
"#version 330 core\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"\n"
"out vec4 color;\n"
"\n"
"uniform sampler2D ourTexture;\n"
"\n"
"void main()\n"
"{\n"
"    color = texture(ourTexture, TexCoord);\n"
"}\n"
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

  GLFWwindow* window = glfwCreateWindow(640, 480, "Family", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  // initialize glew
  glewExperimental = GL_TRUE; 
  glewInit();

  // Define the viewport dimensions
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);  
  glViewport(0, 0, width, height);
  //glViewport(0, 0, 800, 800);

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

  GLfloat vertices[] = {
      // Positions          // Colors           // Texture Coords
       1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Top Right
       //1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
       1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Bottom Right
       //1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
      -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Bottom Left
      //-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
      -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // Top Left 
      //-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
  };
  GLuint indices[] = {  // Note that we start from 0!
      0, 1, 3,   // First Triangle
      1, 2, 3    // Second Triangle
  };


  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO); 
  glGenBuffers(1, &VBO); 
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); 

  // SOIL
  GLuint texture;
  glGenTextures(1, &texture); 
  glBindTexture(GL_TEXTURE_2D, texture);  

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int imageWidth, imageHeight;
  unsigned char* image = SOIL_load_image("family.jpg", &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  //glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0); 
  // /SOIL

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);
            
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glfwTerminate();
  return 0;
}
