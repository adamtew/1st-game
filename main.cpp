// useful libraries - https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
// using image libraries from this
// https://github.com/asamy/Snake
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include <iostream>

// testing
#include "SOIL2.h" 
void triangle()
{
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(640, 480, "Pang", NULL, NULL);
  glfwMakeContextCurrent(window);

  glewInit();

  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // shader
  std::string vertexShaderSourceString = " \
    #version 330 core \
    layout (location = 0) in vec3 position; \
    void main() \
    { \
      gl_Position = vec4(position.x, position.y, position.z, 1.0); \
    } \
    ";
  const GLchar * source = (const GLchar *)vertexShaderSourceString.c_str();
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &source, NULL);
  glCompileShader(vertexShader);
  // /shader
  // fragment shader
  std::string fragmentShaderString = " \
    #version 330 core \
    out vec4 color; \
    void main() { color = vec4(1.0f, 0.5f, 0.2f, 1.0f); } \
  ";
  const GLchar * fragmentShaderSource = (const GLchar *)fragmentShaderString.c_str(); 
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader); 
  // /fragment shader
  // link the shaders
  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glUseProgram(shaderProgram);
  //glDeleteShader(vertexShader);
  //glDeleteShader(fragmentShader);  
  // /link the shaders
  //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  //glEnableVertexAttribArray(0);  
  //GLuint VAO;
  //glGenVertexArrays(1, &VAO);  // available in version 3.0k:w
  //glBindVertexArray(VAO);
  //glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  //glEnableVertexAttribArray(0);  
  //glBindVertexArray(0);
  //glUseProgram(shaderProgram);
  while(!glfwWindowShouldClose(window))
  {
    // Set up our green background color
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    // Clear the entire buffer with our green color (sets the background to be green).
    glClearBufferfv(GL_COLOR, 0, green);

    // Draw our triangles
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  // Program clean up when the window gets closed.
}
void test()
{
  //int save_result = SOIL_save_screenshot("tit", SOIL_SAVE_TYPE_BMP, 0, 0, 1024, 768);

  //if (!glfwInit())
  //{
  //}
  //GLFWwindow* window = glfwCreateWindow(640, 480, "Pang", NULL, NULL);
  //glfwMakeContextCurrent(window);

  //while (!glfwWindowShouldClose(window))
  //{
  //  glClear(GL_COLOR_BUFFER_BIT);
  //  glfwSwapBuffers(window);
  //  glfwPollEvents();
  //}
  //int width, height;
  //unsigned char* image =
  //  SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);

//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
 //               GL_UNSIGNED_BYTE, image);
  //SOIL_free_image_data(image);


  glfwInit();
  GLFWwindow* window = glfwCreateWindow(640, 480, "Pang", NULL, NULL);
  glfwMakeContextCurrent(window);

  GLuint texture;
  glGenTextures(1, &texture);  
  glBindTexture(GL_TEXTURE_2D, texture);  
  // set parameters
  int width, height;
  unsigned char* image = SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  //glGenerateMipmaps(GL_TEXTURE_2D);
  //SOIL_free_image_data(image);
  //glBindTexture(GL_TEXTURE_2D, 0);
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  //glGenTextures(1, &tex_id);
  //GLuint tex_2d = SOIL_load_OGL_texture
  //  (
  //      "./img.png",
  //      SOIL_LOAD_AUTO,
  //      SOIL_CREATE_NEW_ID,
  //      SOIL_FLAG_MIPMAPS |
  //      SOIL_FLAG_INVERT_Y |
  //      SOIL_FLAG_NTSC_SAFE_RGB |
  //      SOIL_FLAG_COMPRESS_TO_DXT
  //  );
  glfwTerminate();

}
// /testing

int main()
{
  std::cout << "hello world\n";
  //Game::Start();
  //test();
  //triangle();
  //return 0;
  //
  GLuint shaderProgram, VBO, vertexShader, fragmentShader, vao;
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(640, 480, "Pang", NULL, NULL);
  glfwMakeContextCurrent(window);

  glewInit();

  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  std::string vertexShaderSourceString = " \
    #version 330 core \
    layout (location = 0) in vec3 position; \
    void main() \
    { \
      gl_Position = vec4(position.x, position.y, position.z, 1.0); \
    } \
    ";
  const GLchar * source = (const GLchar *)vertexShaderSourceString.c_str();
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &source, NULL);
  glCompileShader(vertexShader);
  std::string fragmentShaderString = " \
    #version 330 core \
    out vec4 color; \
    void main() { color = vec4(1.0f, 0.5f, 0.2f, 1.0f); } \
  ";
  const GLchar * fragmentShaderSource = (const GLchar *)fragmentShaderString.c_str(); 
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader); 
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  //glGenVertexArrays(1, &vao);
  //glBindVertexArray(vao);
  glUseProgram(shaderProgram);
  while(!glfwWindowShouldClose(window))
  {
    //static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    //glClearBufferfv(GL_COLOR, 0, green);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  //glDeleteVertexArrays(1, &vao);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}
