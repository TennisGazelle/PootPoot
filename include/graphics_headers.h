#ifndef __GRAPHICS_HEADERS_H_
#define __GRAPHICS_HEADERS_H_

#include <iostream>

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#if defined(__APPLE__) || defined(MACOSX)
  #include <OpenGL/gl3.h>
  #include <OpenGL/GLU.h>
#else //linux as default
  #include <GL/glew.h>
  //#include <GL/glu.h>
#endif

// GLM for matricies
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define INVALID_UNIFORM_LOCATION 0x7fffffff

// add any single definition struct headers here
#include "vertex.h"
#include "direction.h"

static const glm::vec3 GLOBAL_UP = glm::vec3(0.0,1.0,0.0);


#endif /* GRAPHICS_HEADERS_H */
