//
// Created by HP on 9/24/2016.
//
#ifndef __FLYER_CPP_
#define __FLYER_CPP_

#include "flyer.h"

Flyer::Flyer(){
	//default values
	_accelerationVector = glm::vec3(0.0f);
	_velocityVector = glm::vec3(0.0f);
	_radius  = 0;

	//get the model's vertices, and find the longest, furthest one, to set as radius
	for (int i = 0; i < _vertices.size(); i++) {
		_radius = std::max(_radius, _vertices[i].position.length());
	}
}

Flyer::~Flyer() {

}

glm::vec3 Flyer::getVelocityVector() const {
	return _velocityVector;
}

void Flyer::updateVelocityVector(glm::vec3 pVelocityVector) {
	_velocityVector = pVelocityVector;
}

bool Flyer::hasHit(Flyer* otherFlyer) const {
	if (this == otherFlyer)
		return true;

	// if the distance between the relative origins of the two
	// models is closer than the sum of the "farthest" point on
	// either of the two physical models, they hit

	int tolerance = this->_radius + otherFlyer->_radius;
	glm::vec3 distance = glm::vec3(_model[3]) - glm::vec3(otherFlyer->GetModel()[3]);

	return distance.length() < tolerance;
}

void Flyer::setPosition(glm::vec3 pPosition) {
	_model[3] = glm::vec4(pPosition, _model[3][3]);
}

void Flyer::applyForce(glm::vec3 pAccel) {
	_accelerationVector += pAccel;
}

void Flyer::update(unsigned int dt) {
	// move in that given velocity
	glm::vec3 positionVector = glm::vec3(_model[3]);
	positionVector += (0.5f * float(dt * dt) * _accelerationVector);
	positionVector += (float(dt) * _velocityVector);
	_model[3] = glm::vec4(positionVector, _model[3][3]);

	//update those parameters
	_velocityVector += float(dt) * _accelerationVector;
	_accelerationVector *= 0.1;

}

void Flyer::render() {
	Object::Render();
}

#endif


/*
 *
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
 */