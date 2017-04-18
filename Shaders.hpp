#ifndef _SHADERS_HPP
#define _SHADERS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
  static const char* VERTEX_SHADER[] =
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
  enum SHADER { VERTEX, FRAGMENT };
  GLuint shader(SHADER _shader);
  GLuint Get_Vertex_Shader();
  GLuint Get_Fragment_Shader();

};
#endif
