#include <GLFW/glfw3.h>
#include "SplashScreen.hpp"

void SplashScreen::Show(GLFWwindow* window)
{
  
  glfwSetWindowTitle(window, "stuffs");
  glClearColor(1.2f, 0.3f, 0.3f, 1.0f);
  //glClear(GL_COLOR_BUFFER_BIT);
  //glfwSwapBuffers(window);
  //glfwPollEvents();
}
