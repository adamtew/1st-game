// useful libraries - https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
// using image libraries from this
// https://github.com/asamy/Snake
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include <iostream>
#include "SOIL2.h" 

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
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
}
// /testing

int main()
{
  std::cout << "hello world\n";
  //Game::Start();
  //test();
  //triangle();
  //ueturn 0;
  if (!glfwInit())
  {
    std::cout << "failed to initialize\n";
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Make the window resize-able.
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 


  GLuint shaderProgram, VBO, vertexShader, fragmentShader, vao;
  GLFWwindow* window = glfwCreateWindow(640, 480, "Pang", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE; 
  glewInit();

  static const char * vs_source[] =
  {
      "#version 410 core                                                 \n"
      "                                                                  \n"
      "void main(void)                                                   \n"
      "{                                                                 \n"
      "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
      "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
      "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
      "                                                                  \n"
      "    gl_Position = vertices[gl_VertexID];                          \n"
      "}                                                                 \n"
  };
  static const char * fs_source[] =
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

  GLuint program = glCreateProgram();

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, fs_source, NULL);
  glCompileShader(fragmentShader); 

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, vs_source, NULL);
  glCompileShader(vertexShader);


  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glUseProgram(program);

  while(!glfwWindowShouldClose(window))
  {
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}
