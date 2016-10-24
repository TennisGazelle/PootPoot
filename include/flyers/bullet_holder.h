#ifndef __BULLET_HOLDER_CPP_
#define __BULLET_HOLDER_CPP_

#include "object.h"

struct BulletInfo {
	unsigned int life_count;
	glm::mat4 model;
	glm::vec3 direction;
};

class BulletHolder {
public:
	BulletHolder();
	~BulletHolder();
	
	// Update should update all of the individual bullets	
	void Update();
	
	// for rendering graphics' (render) function
	glm::mat4 GetModelAt(unsigned int index);
	
	// making and destroying bullets
	void makeNewBullet(glm::vec3 pDirection, glm::vec3 pInitialPosition);
	void destroyBullet(unsigned int index);
	
private:
	std::vector<BulletInfo> bullets;
	Object* bullet; 
};

#endif