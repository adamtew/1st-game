#ifndef _SHADERS_HPP
#define _SHADERS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>

class Shader
{
  public:
  GLuint Program;
  Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

  void Use();


};
#endif
