#ifndef __ANIMATOR_H_
#define __ANIMATOR_H_

#include "graphics_headers.h"
#include <vector>

enum AnimationType {
	LINEAR,
	EASE_IN,
	EASE_OUT,
	EASE_IN_OUT,

	EASE_IN_OVERSHOOT,
	EASE_OUT_WIND_UP,
};

class Animator {
public:
	Animator();
	~Animator();

	void setAnimationType(AnimationType pAnimationType, unsigned int pDuration);
	void setTargetTransformations(const glm::mat4& begin, const glm::mat4& end);

	glm::mat4 getTransAt(unsigned int index);

private:
	std::vector<glm::mat4> frames;
	AnimationType animationType;
	unsigned int duration;
};

#endif