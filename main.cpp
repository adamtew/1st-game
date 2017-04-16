// useful libraries - https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
// using image libraries from this
// https://github.com/asamy/Snake
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include <iostream>

// testing
#include "SOIL2.h" 
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


  //glfwTerminate();
  GLuint tex_2d = SOIL_load_OGL_texture
    (
        "./img.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS |
        SOIL_FLAG_INVERT_Y |
        SOIL_FLAG_NTSC_SAFE_RGB |
        SOIL_FLAG_COMPRESS_TO_DXT
    );
}
// /testing

int main()
{
  //Game::Start();
  test();
  return 0;
}
