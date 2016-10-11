//
// Created by HP on 9/25/2016.
//

#ifndef __BULLET_CPP_
#define __BULLET_CPP_

#include "bullet.h"

Bullet::Bullet(glm::vec3 pDirection, glm::vec3 pInitialPosition) {
  //check for initial bullet
  if (Object::_vertices.size() == 0) {
    Init("../models/bullet.obj");
  }
  _velocityVector = pDirection;
  _model[3] = glm::vec4(pInitialPosition, _model[3][3]);
  life_count = 500;
}

Bullet::~Bullet(){

}

void Bullet::Update(unsigned int dt) {
  glm::vec3 position = glm::vec3(_model[3]);
  position += float(dt) * _velocityVector;
  _model[3] = glm::vec4(position, _model[3][3]);
  
  life_count--;
}

void Bullet::render() {
	Object::Render();
}

#endif