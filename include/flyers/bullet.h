#ifndef __BULLET_H_
#define __BULLET_H_

#include "flyer.h"

class Bullet : private Flyer {
public:
		Bullet();
		~Bullet();

		//must be overloaded
		void update(unsigned int dt);
		void render();
};

#endif