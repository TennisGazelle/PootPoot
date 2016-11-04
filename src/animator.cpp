#ifndef __ANIMATOR_CPP_
#define __ANIMATOR_CPP_

#include "animator.h"

Animator::Animator() {

}

Animator::~Animator() {

}

void Animator::setAnimationType(AnimationType pAnimationType, unsigned int duration) {
	animationType = pAnimationType;
}

void Animator::setTargetTransformations(const glm::mat4& begin, const glm::mat4& end) {

}

glm::mat4 Animator::getTransAt(unsigned int index) {

}

#endif