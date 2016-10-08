#ifndef __BULLET_H_
#define __BULLET_H_

#include "object.h"

class Bullet : public Object {
public:
	Bullet(glm::vec3 pDirection, glm::vec3 pInitialPosition);
	~Bullet();

	//must be overloaded
	void Update(unsigned int dt);
	void render();

private:
	glm::vec3 _velocityVector;

	//equal for all instances of bullets
	static std::vector<Vertex> _vertices;
	static std::vector<unsigned int> _indices;
	static GLuint _V_BO;
	static GLuint _I_BO;
};

#endif