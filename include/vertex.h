#ifndef __VERTEX_H_
#define __VERTEX_H_

#include "graphics_headers.h"

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;

  Vertex(glm::vec3 v, glm::vec3 c): position(v), color(c) {}
};

#endif
