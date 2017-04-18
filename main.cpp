// useful libraries - https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
// using image libraries from this
// https://github.com/asamy/Snake
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include <iostream>
#include "SOIL2.h" 

namespace Shaders
{

  static const char* FRAGMENT_SHADER[] =
  {
    "#version 410 core                                                 \n"
    "                                                                  \n"
    "out vec4 color;                                                   \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
    "}                                                                 \n"
  };

  static const char* VERTEX_SOURCE[] =
  {
    "#version 410 core                                                 \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "    const vec4 vertices[] = vec4[](vec4( 0.95, -0.95, 0.9, 1.0),  \n"
    "                                   vec4(-0.95, -0.95, 0.9, 1.0),  \n"
    "                                   vec4( 0.95,  0.95, 0.9, 1.0)); \n"
    "                                                                  \n"
    "    gl_Position = vertices[gl_VertexID];                          \n"
    "}                                                                 \n"
  };

  GLuint Get_Vertex_Shader()
  {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, Shaders::VERTEX_SOURCE, NULL);
    glCompileShader(vertexShader);
    return vertexShader;
  }
  GLuint Get_Fragment_Shader()
  {
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, Shaders::FRAGMENT_SHADER, NULL);
    glCompileShader(fragmentShader); 
    return fragmentShader;
  }
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main()
{
  std::cout << "hello world\n";
  //Game::Start();
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

  glewExperimental = GL_TRUE; 
  glewInit();

  GLuint program = glCreateProgram();

  GLuint fragmentShader = Shaders::Get_Fragment_Shader();

  GLuint vertexShader = Shaders::Get_Vertex_Shader();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glUseProgram(program);

  // SOIL - create texture
  int width, height;
  unsigned char* image = SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set filters here

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  while(!glfwWindowShouldClose(window))
  {
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
  glfwTerminate();
  return 0;
}
