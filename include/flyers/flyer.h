#ifndef FLYER_H
#define FLYER_H

#include "../object.h"
#include <tgmath.h>

class Flyer : public Object {
public:
	Flyer();
	~Flyer();

	static Flyer* spawnFlyer();

	glm::vec3 getVelocityVector() const;
	void updateVelocityVector(glm::vec3 pVelocityVector);

	// collision check
	bool hasHit(Flyer* otherFlyer) const;

	// affine transformations
	void applyForce(glm::vec3 pAccel);

	// virtual functions that all must overload
	void update(unsigned int dt);
	void render();

private:
	glm::vec3 _accelerationVector;
	glm::vec3 _velocityVector;

	int _radius;
};


#endif //FLYER_H