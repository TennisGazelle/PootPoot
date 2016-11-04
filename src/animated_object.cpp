#ifndef __ANIMATED_OBJECT_CPP_
#define __ANIMATED_OBJECT_CPP_

#include "animated_object.h"

AnimatedObject::AnimatedObject() {

}

AnimatedObject::~AnimatedObject() {
	
}

void AnimatedObject::Update(unsigned int dt) {
	Object::Update(dt);
}

void AnimatedObject::setTransformation(const glm::mat4 pEnd) {
	animator.setAnimationType(LINEAR, total_duration);
	animator.setTargetTransformations(this->GetModel(), pEnd);
}

glm::mat4 AnimatedObject::GetModel() {
	if (frame_ticker >= total_duration-1)
		return animator.getTransAt(total_duration-1);
	return animator.getTransAt(frame_ticker++);
}

#endif