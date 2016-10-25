#ifndef __BULLET_HOLDER_H_
#define __BULLET_HOLDER_H_

#include "../object.h"

struct BulletInfo {
	unsigned int life_count;
	glm::mat4 model;
	glm::vec4 direction;
};

class BulletHolder {
public:
	BulletHolder();
	~BulletHolder();
	
	// Update should update all of the individual bullets	
	void Update(unsigned int dt);

	// render will render that specific position
	void Render(unsigned int index);
	
	// for rendering graphics' (render) function
	glm::mat4 GetModelAt(unsigned int index);
	
	// making and destroying bullets
	void makeNewBullet(glm::vec3 pDirection, glm::vec3 pInitialPosition);
	void destroyBullet(unsigned int index);

	// check to see if it "hit" what we're giving it
	// will return the integer index with whatever this
	// object collides with, if it doesn't collide with
	// anything, we will return a -1;
	int checkForCollision(const glm::mat4& otherObject);

	// if the bullet goes outside the "space" designated by 
	// the boundary, force them back to the opposite side
	void checkBounds(unsigned int boundary);

	unsigned int getSize() const;
	
private:
	std::vector<BulletInfo> bullets;
	Object* bullet; 
};

#endif