#ifndef __BULLET_HOLDER_CPP_
#define __BULLET_HOLDER_CPP_

#include "bullet_holder.h"

BulletHolder::BulletHolder() {
	// fill the bullet object with a correct 'bullet' that
	// will then be updated with everything to be done 
	// throughout each and every "updating" cycle
}

BulletHolder::~BulletHolder() {
	delete bullet;
	bullet = NULL;
}

void BulletHolder::Update() {
	// go through all the bullet's' and update where
	// they should be going
}

glm::mat4 BulletHolder::GetModelAt(unsigned int index) {
	return mat4(1.0f); //return what would be the model matrix for that index
}

void BulletHolder::makeNewBullet(glm::vec3 pDirection, glm::vec3 pInitialPosition) {

}

void BulletHolder::destroyBullet(unsigned int index) {

}

#endif