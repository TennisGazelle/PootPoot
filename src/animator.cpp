#ifndef __ANIMATOR_CPP_
#define __ANIMATOR_CPP_

#include "animator.h"

Animator::Animator() {

}

Animator::~Animator() {

}

void Animator::setAnimationType(AnimationType pAnimationType, unsigned int pDuration) {
	animationType = pAnimationType;
	duration = pDuration;
}

void Animator::setTargetTransformations(const glm::mat4& begin, const glm::mat4& end) {
	frames.clear();
	glm::mat4 midway_transformation;
	for (int i = 0; i < duration; i++) {

		//if we're doing linear, this is it
		midway_transformation = float(duration - i)/float(duration) * begin;
		midway_transformation += float(i)/float(duration) * end;
		
		frames.push_back(midway_transformation);
	}
}

glm::mat4 Animator::getTransAt(unsigned int index) {
	if (index >= frames.size() || index < 0) 
		return glm::mat4(1.0f);

}

#endif