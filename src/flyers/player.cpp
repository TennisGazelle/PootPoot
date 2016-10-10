//
// Created by HP on 9/25/2016.
//
#ifndef __PLAYER_CPP_
#define __PLAYER_CPP_

#include "player.h"

Player::Player() {
  Init("../models/mainplaner.obj");
}

Player::~Player() {

}

void Player::moveDirection(Direction dir) {
  glm::vec3 pushDirection;
  switch(dir) {
    case UP:
      pushDirection = glm::vec3(0.0,0.0,0.001);
      break;
    case DOWN:
      pushDirection = glm::vec3(0.0,0.0,-0.001);
      break;
    case LEFT:
      pushDirection = glm::vec3(0.001,0.0,0.0);
      break;
    case RIGHT:
      pushDirection = glm::vec3(-0.001,0.0,0.0);
      break;
    default:
      pushDirection = glm::vec3(0.0);
      break;
  }
  applyForce(pushDirection);
}

void Player::shootDirection(Direction dir) {
  switch(dir) {
    case UP:
    default:
      //return new Bullet(glm::vec3(0.0,0.0,0.01), glm::vec3(_model[3]));
      break;
    case DOWN:
      //return new Bullet(glm::vec3(0.0,0.0,-0.01), glm::vec3(_model[3]));
      break;
    case LEFT:
      //return new Bullet(glm::vec3(0.01,0.0,0.0), glm::vec3(_model[3]));
      break;
    case RIGHT:
      //return new Bullet(glm::vec3(-0.01,0.0,0.0), glm::vec3(_model[3]));
      break;
  }
}

void Player::Update(unsigned int dt) {
  Object::Update(dt);
}

void Player::Render() {
  Object::Render();
}

#endif
