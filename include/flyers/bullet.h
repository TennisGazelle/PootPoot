#ifndef __BULLET_H_
#define __BULLET_H_

#include "object.h"

struct BulletInfo {
	glm::mat4 _model;
	int life;
	glm::vec3 _direction;
};

class Bullet : public Object {
public:
	Bullet();
	~Bullet();

	//must be overloaded
	void Update(unsigned int dt);
	void render();
	void RenderAtIndex(int pIndex);

	void makeBullet(glm::vec3 pPosition, glm::vec3 pDirection);

	glm::mat4 GetModelAt(int pIndex);
	int getSize() const;

private:
	std::vector<BulletInfo> _bullets;
};

#endif
