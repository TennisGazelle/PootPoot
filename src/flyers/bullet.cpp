//
// Created by HP on 9/25/2016.
//

#ifndef __BULLET_CPP_
#define __BULLET_CPP_

#include "bullet.h"

Bullet::Bullet() {

}

Bullet::~Bullet(){

}

void Bullet::update(unsigned int dt) {
	//do NOT slow down the acceleration, but die, if the dt is long enough
}

void Bullet::render() {
	Flyer::render();
}

#endif