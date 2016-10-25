#ifndef __BULLET_HOLDER_CPP_
#define __BULLET_HOLDER_CPP_

#include "bullet_holder.h"

BulletHolder::BulletHolder() {
	// fill the bullet object with a correct 'bullet' that
	// will then be updated with everything to be done 
	// throughout each and every "updating" cycle
	bullet = new Object();
	bullet->Init("../models/bullet.obj");
}

BulletHolder::~BulletHolder() {
	delete bullet;
	bullet = NULL;
}

void BulletHolder::Update(unsigned int dt) {
	// go through all the bullet's' and update where
	// they should be going
	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets[i].model[3] += bullets[i].direction;
		bullets[i].life_count--;

		if (bullets[i].life_count < 0) {
			this->destroyBullet(i--);
		}
	}
}

void BulletHolder::Render(unsigned int index) {
	if (index < bullets.size()) {	
		bullet->setPosition(glm::vec3(bullets[index].model[3]));
		bullet->Render();
	}
}

glm::mat4 BulletHolder::GetModelAt(unsigned int index) {
	return index >= bullets.size() ? glm::mat4(1.0f) : bullets[index].model; //return what would be the model matrix for that index
}

void BulletHolder::makeNewBullet(glm::vec3 pDirection, glm::vec3 pInitialPosition) {
	// create new entry
	BulletInfo bulletInfo = {
		50, glm::mat4(1.0f), glm::vec4(pDirection, 0.0f)
	};
	bulletInfo.model[3] = glm::vec4(pInitialPosition, 1.0f);

	bullets.push_back(bulletInfo);
}

void BulletHolder::destroyBullet(unsigned int index) {
	if (index < bullets.size()) {
		bullets.erase(bullets.begin() + index);
	}
}

int BulletHolder::checkForCollision(const glm::mat4& otherObject) {
	for (unsigned int i = 0; i < bullets.size(); i++) {
		if (glm::distance(otherObject[3], bullets[i].model[3]) <= 1.0f) {
			return i;
		}
	}
	return -1;
}

void BulletHolder::checkBounds(unsigned int boundary) {
	glm::vec4 position;

	for (int i = 0; i < bullets.size(); i++) {
		position = bullets[i].model[3];

		if (position.x > boundary) position.x = -boundary;
		else if (position.x < -boundary) position.x = boundary;
		if (position.z > boundary) position.z = -boundary;
		else if (position.z < -boundary) position.z = boundary;

		bullets[i].model[3] = position;
	}
}

unsigned int BulletHolder::getSize() const {
	return bullets.size();
}
#endif