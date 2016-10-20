#ifndef __BULLET_H_
#define __BULLET_H_

#include "object.h"

struct BulletInfo {
	unsigned int life_count;
	glm::mat4 indiv_model;
};

class Bullet : public Object {
public:
	Bullet(glm::vec3 pDirection, glm::vec3 pInitialPosition);
	~Bullet();

	//must be overloaded
	void Update(unsigned int dt);
	void render();

	int life_count;

private:
	glm::vec3 _velocityVector;

	//equal for all instances of bullets
	static std::vector<Vertex> _vertices;
	static std::vector<unsigned int> _indices;
	static GLuint _V_BO;
	static GLuint _I_BO;

};

#endif
