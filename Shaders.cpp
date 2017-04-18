#include "Shaders.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLuint Shaders::shader(Shaders::SHADER _shader)
{
  GLuint shader;
  switch (_shader)
  {
    case VERTEX:
      shader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(shader, 1, Shaders::VERTEX_SHADER, NULL);
      break;
    case FRAGMENT:
      shader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(shader, 1, Shaders::FRAGMENT_SHADER, NULL);
      break;
    default: break;
  }
  glCompileShader(shader);
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
  }
  return shader;
}

GLuint Shaders::Get_Vertex_Shader() { return shader(Shaders::VERTEX); }
GLuint Shaders::Get_Fragment_Shader() { return shader(Shaders::FRAGMENT); }
