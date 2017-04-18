#ifndef _TEXTURES_HPP
#define _TEXTURES_HPP

namespace Textures
{
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
  // /SOIL

};
#endif
