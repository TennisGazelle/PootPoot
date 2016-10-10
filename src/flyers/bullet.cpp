//
// Created by HP on 9/25/2016.
//

#ifndef __BULLET_CPP_
#define __BULLET_CPP_

#include "bullet.h"

Bullet::Bullet() {
  //check for initial bullet
  Object::Init("../models/bullet.obj");
std::cout << "end" << std::endl;
  //initialize all of the bullet structs, if need be
}

Bullet::~Bullet(){

}

void Bullet::makeBullet(glm::vec3 pPosition, glm::vec3 pDirection) {
  // generate the positional model first
  glm::mat4 pos = glm::mat4(1.0);
  pos[3] = glm::vec4(pPosition, pos[3][3]);

  BulletInfo nBullet = { pos, 50, pDirection };

  _bullets.push_back(nBullet);
}

glm::mat4 Bullet::GetModelAt(int pIndex) {
	if (pIndex > _bullets.size())
		pIndex = 0;
	return _bullets[pIndex]._model;
}

int Bullet::getSize() const {
	return _bullets.size();
}

void Bullet::Update(unsigned int dt) {
  glm::vec3 position;

  // go through all the preexisting bullets
  for (int i = 0; i < _bullets.size(); i++) {
     // decrement life, and remove if necessary
     _bullets[i].life--;

    if (_bullets[i].life == 0) {
      _bullets.erase(_bullets.begin()+i);
      i--;
    }

    //do what we're doing up there
    position = glm::vec3(_bullets[i]._model[3]);
    position += float(dt) * _bullets[i]._direction;
    _bullets[i]._model[3] = glm::vec4(position, _bullets[i]._model[3][3]);
  }



}

void Bullet::render() {
	//Object::Render();
	// go through each of the other objects, and render as if we were them
	for (int i = 0; i < _bullets.size(); i++) {
		this->_model = _bullets[i]._model;
		Object::Render();
	}
}

void Bullet::RenderAtIndex(int pIndex) {
	if (pIndex > _bullets.size()) {
		pIndex = 0;
	}

	this->_model = _bullets[pIndex]._model;
	Object::Render();
}
#endif
