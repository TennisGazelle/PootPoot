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

}

#endif

/*
 *
class Player : public Flyer {
public:
	Player();
	~Player();

	void moveDirection(Direction dir);
	void shootDirection(Direction dir);

private:

};
 */