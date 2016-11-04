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

void Flyer::applyForce(glm::vec3 pAccel) {
	_accelerationVector += pAccel;
}

float angleBetweenTwoVectors(const glm::vec3& first, const glm::vec3& second) {
	return acos(glm::dot(first, second)/(first.length() * second.length())) * M_PI / 180.0f;
	//return acos(glm::dot(first, second));
}

void Flyer::update(unsigned int dt) {
	// move in that given velocity
	glm::vec3 positionVector = glm::vec3(_model[3]);
	positionVector += (0.5f * float(dt * dt) * _accelerationVector);
	positionVector += (float(dt) * _velocityVector);

	//update those parameters
	_velocityVector += float(dt) * _accelerationVector;
	_velocityVector *= 0.94;
	_accelerationVector *= 0.1;

	//change position and otherwise
	_model[3] = glm::vec4(positionVector, _model[3][3]);
}

void Flyer::render() {
	Object::Render();
}

glm::mat4 Flyer::GetModel() {
	static float turn = 0.0f;
	turn += angleBetweenTwoVectors(glm::vec3(0,1,0), _velocityVector);
	glm::mat4 rTransform = glm::rotate(glm::mat4(1.0f), turn, glm::vec3(0.0,1.0,0.0));
	return _model * rTransform;
}
#endif