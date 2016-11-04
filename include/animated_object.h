#ifndef __ANIMATED_OBJECT_H
#define __ANIMATED_OBJECT_H

#include "animator.h"
#include "object.h"

class AnimatedObject : public Object {
public:
	AnimatedObject();
	~AnimatedObject();
	void Update(unsigned int dt);
	void setTransformation(const glm::mat4 pEnd);
	
	glm::mat4 GetModel();

private:
	Animator animator;
	unsigned int frame_ticker;
	static const int total_duration = 100;
};
#endif
/*
    void Update(unsigned int dt);
	GetModel();

	setPostioin(vec3 position)
	setModel()?
*/