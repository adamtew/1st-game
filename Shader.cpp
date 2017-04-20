#include "Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
  // 1. Get code from files
  std::string vertexCode, fragmentCode;
  std::ifstream vertexShaderFile;
  std::ifstream fragmentShaderFile;

  vertexShaderFile.exceptions (std::ifstream::badbit);
  fragmentShaderFile.exceptions (std::ifstream::badbit);
  try
  {
    vertexShaderFile.open(vertexPath);
    fragmentShaderFile.open(fragmentPath);

    std::stringstream vertexShaderStream, fragmentShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    vertexShaderFile.close();
    fragmentShaderFile.close();
    vertexCode = vertexShaderStream.str();
    fragmentCode = fragmentShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
  }
  const GLchar* vertexShaderCode = vertexCode.c_str();
  const GLchar* fragmentShaderCode = fragmentCode.c_str();

  // 2. Compile code
  GLuint vertex, fragment;
  GLint success;
  GLchar infolog[512];
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infolog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  {
    glGetShaderInfoLog(fragment, 512, NULL, infolog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
  }

  // 3. Make program
  this->Program = glCreateProgram();
  glAttachShader(this->Program, vertex);
  glAttachShader(this->Program, fragment);
  glLinkProgram(this->Program);

  glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(this->Program, 512, NULL, infolog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << "\n";
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}


void Shader::Use()
{
  glUseProgram(this->Program);
}
