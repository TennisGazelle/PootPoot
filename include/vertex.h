#ifndef __VERTEX_H_
#define __VERTEX_H_

#include "graphics_headers.h"

struct Vertex
{
  glm::vec3 vertex;
  glm::vec3 color;

  Vertex(glm::vec3 v, glm::vec3 c): vertex(v), color(c) {}
};

#endif
