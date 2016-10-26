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
		std::cout << "life count for bullet: " << i << " is now: " << bullets[i].life_count << std::endl;
		if (bullets[i].life_count <= 0) {
			this->destroyBullet(i);
			i--;
		}
	}
	bullet->Update(dt);
}

void BulletHolder::Render(unsigned int index) {
	if (index < bullets.size()) {
		bullet->Render();
	}
}

glm::mat4 BulletHolder::GetModelAt(unsigned int index) {
	return index >= bullets.size() ? glm::mat4(1.0f) : bullets[index].model; //return what would be the model matrix for that index
}

void BulletHolder::makeNewBullet(glm::vec3 pDirection, glm::vec3 pInitialPosition) {
	// create new entry
	BulletInfo bulletInfo = {
		500, glm::mat4(1.0f), glm::vec4(pDirection, 0.0f) 
	};
	bulletInfo.model[3] = glm::vec4(pInitialPosition+(100.0f*pDirection), bulletInfo.model[3][3]);

	bullets.push_back(bulletInfo);
}

void BulletHolder::destroyBullet(unsigned int index) {
	if (index < bullets.size()) {
		bullets.erase(bullets.begin() + index);
	}
}

int BulletHolder::checkForCollision(const glm::mat4& otherObject) {
	for (unsigned int i = 0; i < bullets.size(); i++) {
		if (glm::distance(glm::vec3(otherObject[3]), glm::vec3(bullets[i].model[3])) <= 1.0f) {
			return i;
		}
	}
	return -1;
}

void BulletHolder::checkBounds(int boundary) {
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