#ifndef FLYER_H
#define FLYER_H

#include "../object.h"

class Flyer : private Object {
public:	
	Flyer();
	~Flyer();

	static Flyer* spawnFlyer();
	
	glm::vec3 getVelocityVector() const;
	void updateVelocityVector(glm::vec3 pVelocityVector);

	// collision check
	bool hasHit() const;

	// affine transformations
	void setPosition(glm::vec3 pPosition);
	void applyForce(glm::vec3 pAccel);

	// virtual functions that all must overload
	virtual void update(unsigned int dt) = 0;
	virtual void render() = 0;

private:
	glm::vec3 _accelerationVector;
	glm::vec3 _velocityVector;
	int _radius;
	
};


#endif //FLYER_H